#ifndef util_H
#define util_H 1 
#define info_out(X) std::cout<<"==> "<<__LINE__<<" "<<#X<<" |"<<(X)<<"|\n"
#define debug_out(X) std::cerr<<"==> "<<__LINE__<<" "<<#X<<" |"<<(X)<<"|\n"
#include <iostream>
#include <string>
#include <tuple>
#include <string>
#include <array>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <concepts>
#include <climits>
#include <mutex>
#include <chrono>

#include <QColor>
#include <QTextEdit>
#include <QLayout>

#include "modbus/modbus.h"
namespace util{

static std::mutex g_mutex;

struct modbus_parameters_t{
  int baud = 19200;
  char parity = 'N';
  int data_bit = 8;
  int stop_bit = 2; };

std::string uint2timestr(uint32_t);

static const char blank_str[] = QT_TRANSLATE_NOOP("mainwindow", "N/A");

static std::array<QColor,3> color_palette = { 
  QColor{"#07B2FC"}, QColor{"#534F02"}, QColor{"#F80F05"} };

enum class log_mode : size_t{ k_info = 0 ,k_warning ,k_error };

std::string qlayout_sizeconstraint_name(QLayout::SizeConstraint);

std::string format_time(std::chrono::system_clock::duration,double);


std::string const item_names[] = {
  "Mfc_rate_sv_LH, "
  "Mfc_rate_sv_HI, "
  "Mfc_rate_default_LH, "
  "Mfc_rate_default_HI, "
  "Mfc_rate_pv_LH, "
  "Mfc_rate_pv_HI, "
  "Pump_speed_sv, "
  "Pump_speed_default, "
  "Pump_speed_pv, "
  "Pump_speed_min, "
  "Pump_speed_max, "
  "Temperature_dec, "
  "Temperature_fra, "
  "Pressure_dec, "
  "Pressure_fra, "
  "Set_mode, "
  "Cur_mode, "
  "Cur_status, "
  "Flow_duration, "
  "Recycle_duration, "
  "Update_interval, "
  "Reg_heartbeat_LH, "
  "Reg_heartbeat_HI" };


std::string rename(std::string const&);
std::string pwd();
std::string get_str(uint16_t const* addr);
float get_bmp280(uint16_t *, size_t=6);

float get_bmp280_1(uint16_t*);

float to_float(uint16_t* view);

void t_msleep(size_t);

std::string u162hexstr(uint16_t);

std::string timestamp();

int64_t highrestime_ns();
int64_t highrestime_ms();

std::string time_to_str();

std::pair<modbus_t*,bool> connect_modbus(
    char const* device
    ,int baud
    ,int parity
    ,int data_bit
    ,int stop_bit
    ,int const slave_addr);

template <class _tp, class... args>
void to_stream(_tp& os,args&&... params){
  auto const& to_stream_impl = []<class _sp, class _tup>(_sp& os, _tup const& tup){
    constexpr std::size_t NN = std::tuple_size_v<_tup>;
    [&]<size_t... I>(std::index_sequence<I...>){
      auto* addr = std::addressof(os);
      (...,(*addr<<" "<<std::get<I>(tup)));
    }(std::make_index_sequence<NN>()); };
  to_stream_impl(os,std::make_tuple(std::forward<args>(params)...)); }

template <class _tp=QTextEdit, log_mode _ev=log_mode::k_info,class... args>
_tp* info_to(_tp* qtext, args&&... params){
  if (qtext->document()->lineCount() >= 101) qtext->clear();
  qtext->setTextColor(color_palette[(size_t)_ev]);
  std::stringstream sstr;
  to_stream(sstr
      ,_ev==log_mode::k_info ? "[INFO] " : _ev==log_mode::k_warning ? "[WARN] " : "[ERROR]"
#ifdef WIN32
      ,'[',util::highrestime_ns(),']'
#else
      ,util::timestamp()
#endif
      //,get_time()
      ,std::forward<args>(params)...);
  {std::lock_guard<std::mutex> lock(g_mutex); qtext->append(QString{sstr.str().c_str()});}
  return qtext; }

template <std::integral _tp>
inline bool bit(_tp const v,uint8_t addr=0){
  if (addr>=sizeof(_tp)*__CHAR_BIT__) throw std::out_of_range("");
  _tp mask = v>>addr;
  return mask&1; }

template <std::integral _tp>
inline void bit(_tp& v,uint8_t addr,bool s){
  if (addr>=sizeof(_tp)*__CHAR_BIT__) throw std::out_of_range("");
  _tp mask = _tp(1);
  if (s) v |= (mask<<addr);
  else v &= ~(mask<<addr);
}

template <std::integral _tp>
inline void bit_ot(_tp& v, uint8_t addr){
}

template <std::integral _tp>
inline void bit_sw(_tp& a,_tp& b){ a^=b; b^=a; a^=b; }

std::string state_ss(bool v);

}

namespace util{
static std::index_sequence<8,8,8,8> const b2i_indx;
static std::index_sequence<8,8> const b2u16_indx;
static std::index_sequence<16,16> const u162u32_indx;
namespace _meta{

template <class _tp, template <class, class...> class _cont_tt=std::vector
  ,template <class...> class _tup_t=std::tuple, class... _args>
_cont_tt<_tp> unpack(_tup_t<_args...> const& _p0){
  constexpr std::size_t NN = sizeof...(_args);
  _cont_tt<_tp> tmp(NN);
  [&]<std::size_t... I>(std::index_sequence<I...>){
    (...,(tmp.at(I) = static_cast<_tp>(std::get<I>(_p0))));
  }(std::make_index_sequence<NN>()); 
  return tmp; }

template <std::size_t N>
struct size_{
  constexpr std::size_t static value = N; };

template <std::size_t N, std::size_t M, std::size_t value_first, std::size_t... _values>
struct get_helper{
  constexpr std::size_t static value = get_helper<N,M+1,_values...>::value; };
template <std::size_t N, std::size_t value_first, std::size_t... _values>
struct get_helper<N,N,value_first,_values...>{
  constexpr std::size_t static value = value_first; };

template <std::size_t N, class...>
struct get;

template <std::size_t N, std::size_t... _values>
requires (N<=(sizeof...(_values)-1))
struct get<N,std::index_sequence<_values...>>{
  constexpr static std::size_t value = get_helper<N,0,_values...>::value;};

template <std::size_t N, std::size_t... _values>
requires (N<=(sizeof...(_values)-1))
struct get_c{
  constexpr static std::size_t value = get_helper<N,0,_values...>::value;};

template <std::size_t _index_l, std::size_t _index_u, std::size_t... _values>
requires (_index_l>=0 && _index_u<=sizeof...(_values) && _index_l<=_index_u)
struct range_sum_helper{
  static constexpr std::size_t value = get_c<_index_l,_values...>::value
    + range_sum_helper<_index_l+1,_index_u,_values...>::value; };
template <std::size_t _index_l, std::size_t... _values>
struct range_sum_helper<_index_l,_index_l,_values...>{
  static constexpr std::size_t value = 0UL; };

//I don't know(or don't want) to unify 'range_sum' and 'range_sum_c', so please make do with it;
// so as 'get'
//I don't have the energy to talk about those unified algorithms, maybe you can seek help from "boost::mpl" and "boost::mp11"
template <std::size_t,std::size_t,class... _args>
struct range_sum;

template <std::size_t _index_l, std::size_t _index_u, std::size_t... _values>
struct range_sum<_index_l,_index_u,std::index_sequence<_values...>>{
  static constexpr std::size_t value = 
    range_sum_helper<_index_l,_index_u,_values...>::value; };

template <std::size_t _index_l,std::size_t _index_u,std::size_t... _values>
struct range_sum_c{
  static constexpr std::size_t value = 
    range_sum_helper<_index_l,_index_u,_values...>::value; };

template <class _tp, class _up=_tp, class... _args, std::size_t... _values>
requires std::unsigned_integral<_tp> && (sizeof...(_args)>=sizeof...(_values))
void encode(_tp& _dest,std::index_sequence<_values...>
    ,_args&&... _codes){
  _dest = (std::numeric_limits<_tp>::min)();
  constexpr static std::size_t NN = sizeof...(_values);
  auto codes = unpack<_up>(std::make_tuple(std::forward<_args>(_codes)...));
  [&]<std::size_t... I>(std::index_sequence<I...>){
    (...,(_dest |= codes.at(I) <<(range_sum_c<I+1,NN,_values...>::value)));
  }(std::make_index_sequence<NN>{}); }

template <class _tp, std::size_t N>
requires (std::unsigned_integral<_tp> && N<=__CHAR_BIT__*sizeof(_tp))
_tp decode_helper(_tp const& _p0){
  _tp bs = (std::numeric_limits<_tp>::max)();
  bs >>= sizeof(_tp)*__CHAR_BIT__-N;
  return _p0 & bs; }
template<class _tp, class _up=_tp, std::size_t... _values>
std::array<_up,sizeof...(_values)> decode(_tp const& _from, std::index_sequence<_values...>){
  constexpr static std::size_t NN = sizeof...(_values);
  std::array<_up,NN> tmp{};
  [&]<std::size_t... I>(std::index_sequence<I...>){
    (...,(tmp.at(NN-I-1)=decode_helper<_up,get_c<I,_values...>::value>(static_cast<_up>(_from>>range_sum_c<I+1,NN,_values...>::value))));
  }(std::make_index_sequence<NN>{});
  return tmp; }
}
}

namespace meta = util::_meta;

#endif
