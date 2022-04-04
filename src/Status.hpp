#ifndef STATUS_HPP
#define STATUS_HPP

/** \file statstruct.hpp
 * Holds structure that holds station status
 */

/** \struct
 * This structure is used to hold information about availability of sensor or module.
 */
typedef struct
{
    bool cardAvailable = true; /**< Whetever or not SD card is available*/
    bool bmeAvailable = true; /**< Whetever or not BME680 is available*/
    bool rtcAvailable = true; /**< Whetever or not RTC module is available*/
    bool spsAvailable = true; /**< Whetever or not is sps30 sensor is available*/
    bool problemOccured = false; /**< Whetever or not problem occured*/
} status_t;

#endif