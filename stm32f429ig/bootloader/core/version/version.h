#ifndef VERSION_H
#define VERSION_H

/*
 * Semantic version: MAJOR.MINOR.PATCH
 *
 * Update these values when publishing a new version, for example:
 *
 *   #define VERSION_MAJOR 1
 *   #define VERSION_MINOR 2
 *   #define VERSION_PATCH 3
 */
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0

#define VERSION_STRINGIFY_IMPL(value) #value
#define VERSION_STRINGIFY(value)      VERSION_STRINGIFY_IMPL(value)

/* Full semantic version string, for example "1.2.3". */
#define VERSION_STRING                                                                             \
    VERSION_STRINGIFY(VERSION_MAJOR)                                                               \
    "." VERSION_STRINGIFY(VERSION_MINOR) "." VERSION_STRINGIFY(VERSION_PATCH)

/* Numeric form: 1.2.3 becomes 0x010203. */
#define VERSION_HEX ((VERSION_MAJOR << 16) | (VERSION_MINOR << 8) | VERSION_PATCH)

/* True when the current core version is at least major.minor.patch. */
#define VERSION_CHECK(major, minor, patch)                                                         \
    (VERSION_MAJOR > (major) || (VERSION_MAJOR == (major) && VERSION_MINOR > (minor)) ||           \
     (VERSION_MAJOR == (major) && VERSION_MINOR == (minor) && VERSION_PATCH >= (patch)))

#endif /* VERSION_H */
