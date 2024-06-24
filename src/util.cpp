#include "util.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include <thread>
#include <chrono>
#include <bitset>
#include <stdexcept>
#include <cmath>
#include <ctime>
#include <iomanip>

namespace util{

std::string state_ss(bool v){ return  v ? "background: green;" : "background: red;";}

std::string rename(std::string const& name){
  if (name.length()<=1) return name;
  char c = name.back();
  if(c=='_' || c=='-') return name+"_0";
  if (!std::isdigit(c)) return name+"0";
  return name.substr(0,name.length()-1)+std::string{(char)(c+1)}; }

std::string pwd(){ 
  char buff[FILENAME_MAX]; getcwd(buff,FILENAME_MAX); return {buff}; }

std::pair<modbus_t*,bool> connect_modbus(
    char const* device
    ,int baud
    ,int parity
    ,int data_bit
    ,int stop_bit
    ,int const slave_addr){
  std::pair<modbus_t*,bool> rt;
  auto* modbus_ctx = modbus_new_rtu(device,baud,parity,data_bit,stop_bit);
  modbus_set_slave(modbus_ctx,slave_addr);
  modbus_set_response_timeout(modbus_ctx,0,500000);
  modbus_set_debug(modbus_ctx,1);
  modbus_set_error_recovery(modbus_ctx,
      modbus_error_recovery_mode(MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL));
  int ec = modbus_connect(modbus_ctx);
  bool status = (ec==0);
  if (!status){ modbus_close(rt.first); modbus_free(rt.first); rt.first = nullptr; return {nullptr,true};}
  return {modbus_ctx,true}; }

void t_msleep(size_t value){
  std::this_thread::sleep_for(std::chrono::milliseconds(value)); }

float to_float(uint16_t* view){
  uint32_t v10 = std::bitset<32>{std::bitset<16>{view[1]}.to_string()+
    std::bitset<16>{view[0]}.to_string()}.to_ulong();
  float* curr_f = reinterpret_cast<float*>(&v10);
  return curr_f[0]; };

std::string timestamp(){
  char buffer[80]; time_t timer = time(0);
  struct tm* tt = localtime(&timer);
  strftime(buffer,81,"%Y-%m-%d %H:%M:%s",tt);
  return "["+std::string{buffer}+"]"; }

//int64_t highrestime_ns(){
//  return std::chrono::duration_cast<std::chrono::steady_clock::duration>(
//      std::chrono::steady_clock::now().time_since_epoch()
//      ).count(); }
//int64_t highrestime_ms(){
//  return std::chrono::duration_cast<std::chrono::steady_clock::duration>(
//      std::chrono::steady_clock::now().time_since_epoch()
//      ).count()/1000000; }
int64_t highrestime_ns(){
  return std::chrono::duration_cast<std::chrono::system_clock::duration>(
      std::chrono::system_clock::now().time_since_epoch()
      ).count(); }
int64_t highrestime_ms(){
  return std::chrono::duration_cast<std::chrono::system_clock::duration>(
      std::chrono::system_clock::now().time_since_epoch()
      ).count()/1000000; }

std::string get_str(uint16_t const* addr){
  char buf[16];
  sprintf(buf,"%3d",addr[0]);
  uint32_t fv = uint32_t(addr[1]<<16)+addr[2];
  sprintf(buf+3,"%03d",fv);
  return std::string(buf,buf+3)+"."+std::string(buf+3); }

float get_bmp280(uint16_t* view, size_t fl){
  std::string i = std::to_string(view[0]);
  std::string f = std::to_string((uint32_t)(view[1]<<16)+(uint32_t)view[2]);
  fl = fl>f.length() ? f.length() : fl;
  std::string r = i+"."+f.substr(0,fl);
  float rt{};
  try{ rt = std::stof(r.c_str()); }catch(std::invalid_argument const& e){ rt = std::nanf(""); }
  return rt; }


float get_bmp280_1(uint16_t* view){
  std::string i = std::to_string(view[0]);
  std::string f = std::to_string(view[1]);
  std::string r = i+"."+f;
  float rt{};
  try{ rt = std::stof(r.c_str()); }catch(std::invalid_argument const& e){ rt = std::nanf(""); }
  return rt; }

std::string time_to_str(){
  using namespace std::chrono;
  system_clock::time_point tp_now = system_clock::now();
  system_clock::duration dsp = tp_now.time_since_epoch();
  time_t msp = duration_cast<microseconds>(dsp).count();
  time_t sse = msp/1000000;
  std::tm ct = *std::localtime(&sse);
  std::stringstream sstr;
  sstr<<1900 + ct.tm_year << "-"<<1+ ct.tm_mon << "-" << ct.tm_mday
    <<"_"<<ct.tm_hour<<"-"<<ct.tm_min<<"-"<<ct.tm_sec<<"_"<< msp%1000000;
  return sstr.str(); }

std::string uint2timestr(uint32_t value){
  uint16_t hour = value/3600; uint16_t min = (value%3600)/60; uint16_t sec = value-3600*hour-min*60;
  std::string result(""); if (hour>=1) result += std::to_string(hour)+":";
  result += std::to_string(min) + ":"; result += std::to_string(sec); return result; }

std::string u162hexstr(uint16_t value){
  std::stringstream sstr; sstr<<"0x"<<std::hex<<value; return sstr.str(); }

std::string qlayout_sizeconstraint_name(QLayout::SizeConstraint t){
  return t==QLayout::SetDefaultConstraint ?
    "QLayout::SetDefaultConstraint" :
    t==QLayout::SetFixedSize ? "QLayout::SetFixedSize" :
    t==QLayout::SetMinimumSize ? "QLayout::SetMinimumSize" :
    t==QLayout::SetMaximumSize ? "QLayout::SetMaximumSize" :
    t==QLayout::SetMinAndMaxSize ? "QLayout::SetMinAndMaxSize" :
    t==QLayout::SetNoConstraint ? "QLayout::SetNoConstraint" : "unkonw";
}

std::string format_time(std::chrono::system_clock::duration start
    ,double v){
  using namespace std::chrono;
  auto d = start+milliseconds((int)v);
  //auto d = system_clock::now().time_since_epoch()+seconds((int)v);
  time_t tt = duration_cast<microseconds>(d).count();
  tt/=1000000;
  std::tm ct = *std::localtime(&tt);
  std::stringstream sstr;
  auto const& il00 = [](size_t vv)->std::string{
    if (vv<=9) return std::string("0")+std::to_string(vv);
    return std::to_string(vv); };
  sstr<<il00(ct.tm_hour)<<":"<<il00(ct.tm_min)<<":"<<il00(ct.tm_sec);
  return sstr.str();
}


}
