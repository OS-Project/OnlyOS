/*
    Created by Thibault on 12/05/16.
*/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ONLYOS_RTC_H
#define ONLYOS_RTC_H
    void RTC_init(char rtc_number);
    void RTC_start(char rtc_number);
    void RTC_stop(char rtc_number);

    unsigned int RTC_getTime(char rtc_number);
    unsigned int RTC_getCalendar(char rtc_number);
    unsigned int RTC_getPhysicalAdress(char rtc_number);
#endif

#ifdef __cplusplus
}
#endif