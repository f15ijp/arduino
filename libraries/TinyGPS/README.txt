From http://arduiniana.org/libraries/tinygps/


A Compact Arduino GPS/NMEA Parser

Note: TinyGPS 12 is now available.  TinyGPS 12 provides several new features:

    satellites() – Number of satellites counter from $GPRMC
    hdop() – Horizontal Dilution of Precision from $GPRMC — the smaller this value is the more confidence you have in the accuracy of the location reading.
    course_to() – another Maarten Lamers’ borrowing that complements his distance_to
    cardinal() – a nice little static function by Matt Monson that converts a course to a compass direction like “SSE”.

Note: TinyGPS 11 is now Arduino 1.0 compatible.

TinyGPS is designed to provide most of the NMEA GPS functionality I imagine an Arduino user would want – position, date, time, altitude, speed and course – without the large size that seems to accompany similar bodies of code.  To keep resource consumption low, the library avoids any floating point dependency and ignores all but a few key GPS fields.
Usage

To use, simply create an instance of an object like this:

#include "TinyGPS.h"
TinyGPS gps;

Feed the object serial NMEA data one character at a time using the encode() method. (TinyGPS does not handle retrieving serial data from a GPS unit.) When encode() returns “true”, a valid sentence has just changed the TinyGPS object’s internal state. For example:

#define RXPIN 3
#define TXPIN 2
SoftwareSerial nss(RXPIN, TXPIN);
void loop()
{
  while (nss.available())
  {
    int c = nss.read();
    if (gps.encode(c))
    {
      // process new gps info here
    }
  }
}

You can then query the object to get various tidbits of data. To test whether the data returned is stale, examine the (optional) parameter “fix_age” which returns the number of milliseconds since the data was encoded.

long lat, lon;
unsigned long fix_age, time, date, speed, course;
unsigned long chars;
unsigned short sentences, failed_checksum;

// retrieves +/- lat/long in 100000ths of a degree
gps.get_position(&lat, &lon, &fix_age);

// time in hhmmsscc, date in ddmmyy
gps.get_datetime(&date, &time, &fix_age);

// returns speed in 100ths of a knot
speed = gps.speed();

// course in 100ths of a degree
course = gps.course();

Statistics

The stats method provides a clue whether you are getting good data or not. It provides statistics that help with troubleshooting.

// statistics
gps.stats(&chars, &sentences, &failed_checksum);

    chars
    - the number of characters fed to the object

    sentences
    - the number of valid $GPGGA and $GPRMC sentences processed

    failed_checksum
    - the number of sentences that failed the checksum test

Integral values

Values returned by the core TinyGPS methods are integral. Angular latitude and longitude measurements, for example, are provided in units of 10-5 degrees, so instead of 90°30’00″, get_position() returns a longitude value of 9050000, or 90.5 degrees. But…
Using Floating Point

…for applications which are not resource constrained, it may be more convenient to use floating-point numbers. For these, TinyGPS offers several inline functions that return more easily-managed data. Don’t use these unless you can afford to link the floating-point libraries. Doing so may add 2000 or more bytes to the size of your application.

float flat, flon;

// returns +/- latitude/longitude in degrees
gps.f_get_position(&flat, &flon, &fix_age);
float falt = gps.f_altitude(); // +/- altitude in meters
float fc = gps.f_course(); // course in degrees
float fk = gps.f_speed_knots(); // speed in knots
float fmph = gps.f_speed_mph(); // speed in miles/hr
float fmps = gps.f_speed_mps(); // speed in m/sec
float fkmph = gps.f_speed_kmph(); // speed in km/hr

Date/time cracking

For more convenient access to date/time use this:

int year;
byte month, day, hour, minutes, second, hundredths;
unsigned long fix_age;

gps.crack_datetime(&year, &month, &day,
  &hour, &minute, &second, &hundredths, &fix_age);

Establishing a fix

TinyGPS objects depend on an external source, i.e. its host program, to feed valid and up-to-date NMEA GPS data. This is the only way to make sure that TinyGPS’s notion of the “fix” is current. Three things must happen to get valid position and time/date:

    You must feed the object serial NMEA data.
    The NMEA sentences must pass the checksum test.
    The NMEA sentences must report valid data. If the $GPRMC sentence reports a validity of “V” (void) instead of “A” (active), or if the $GPGGA sentence reports fix type “0″ (no fix) then those sentences are discarded.

To test whether the TinyGPS object contains valid fix data, pass the address of an unsigned long variable for the “fix_age” parameter in the methods that support it. If the returned value is TinyGPS::GPS_INVALID_AGE, then you know the object has never received a valid fix. If not, then fix_age is the number of milliseconds since the last valid fix. If you are “feeding” the object regularly, fix_age should probably never get much over 1000. If fix_age starts getting large, that may be a sign that you once had a fix, but have lost it.

float flat, flon;
unsigned long fix_age; // returns +- latitude/longitude in degrees
gps.f_get_position(&flat, &flon, &fix_age);
if (fix_age == TinyGPS::GPS_INVALID_AGE)
  Serial.println("No fix detected");
else if (fix_age > 5000)
  Serial.println("Warning: possible stale data!");
else
  Serial.println("Data is current.");

Interfacing with Serial GPS

To get valid and timely GPS fixes, you must provide a reliable NMEA sentence feed. If your NMEA data is coming from a serial GPS unit, connect it to Arduino’s hardware serial port, or, if using a “soft” serial port, make sure that you are using a reliable SoftSerial library. As of this writing (Arduino 0013), the SoftwareSerial library provided with the IDE is inadequate. It’s best to use my NewSoftSerial library, which builds upon the fine work ladyada did with the AFSoftSerial library.
Library Version

You can retrieve the version of the TinyGPS library by calling the static member library_version().

int ver = TinyGPS::library_version();

Resource Consumption

Linking the TinyGPS library to your application adds approximately 2500 bytes to its size, unless you are invoking any of the f_* methods. These require the floating point libraries, which might add another 600+ bytes.
Download

The latest version of TinyGPS is available here: TinyGPS12.zip
Change Log

    initial version
    << streaming, supports $GPGGA for altitude, floating point inline functions
    also extract lat/long/time from $GPGGA for compatibility with devices with no $GPRMC
    bug fixes
    API re-org, attach separate fix_age’s to date/time and position.
    Prefer encode() over operator<<. Encode() returns boolean indicating whether TinyGPS object has changed state.
    Changed examples to use NewSoftSerial in lieu of AFSoftSerial; rearranged the distribution package.
    Greater precision in latitude and longitude.  Angles measured in 10-5 degrees instead of 10-4 as previously.  Some constants redefined.
    Minor bug fix release: the fix_age parameter of get_datetime() was not being set correctly.
    Added Maarten Lamers’ distance_to() as a static function.
    Arduino 1.0 compatibility
    Added satellites(), hdop(), course_to(), and cardinal()

Acknowledgements

Many thanks to Arduino forum users mem and Brad Burleson for outstanding help in alpha testing this code. Thanks also to Maarten Lamers, who wrote the wiring library that originally gave me the idea of how to organize TinyGPS.  Thanks also to Dan P. for suggesting that I increase the lat/long precision in version 8.  Thanks to many people who suggested new useful features for TinyGPS, especially Matt Monson, who wrote some nice sample code to do so.

All input is appreciated.

Mikal Hart
