#ifndef IPGEO_H
#define IPGEO_H

/**
 * Function: get_geo_info
 * ----------------------
 * Retrieves geolocation information for a given IP address
 * using the ipinfo.io API.
 *
 * Parameters:
 *   ipAddress - User-provided IP address string
 *   city, region, country, org, loc - Output buffers to store parsed data
 *
 * Returns:
 *   0 if successful, 1 if an error occurred.
 */
int get_geo_info(const char *ipAddress,
                 char *city,
                 char *region,
                 char *country,
                 char *org,
                 char *loc);

#endif // IPGEO_H
