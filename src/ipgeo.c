// Programmer:       Brian Lorick
// Date:             10/28/2025
// Program Name:     GeoLocator (IP Address Geolocation Lookup)
// Chapter:          Internet and API Integration
// Description:      The program prompts the user for an IP address,
//                   retrieves geolocation information (city, region,
//                   country, organization, and coordinates) from the
//                   ipinfo.io API using the curl command.
//                   It handles invalid or unreachable IPs gracefully.

#define _CRT_SECURE_NO_WARNINGS // Disable warnings for scanf and fopen

#include <stdio.h>   // For printf, scanf, fopen, fgets, etc.
#include <stdlib.h>  // For system(), remove(), malloc(), free()
#include <string.h>  // For string handling functions like strstr and strlen
#include "ipgeo.h"   // Our custom header file

int main(void) // Main function where program execution begins
{

    // ------------------------------------------------------------
    // Constant and Variable Declarations
    // ------------------------------------------------------------

    const int MAX_URL_LENGTH = 256; // Maximum length for URL strings
    const int MAX_LINE_LENGTH = 512; // Maximum length for lines read from file
    const char TEMP_FILE[] = "geo_temp.json"; // Temporary file name for API response

    char ipAddress[100] = ""; // Variable to store user input for IP address
    char city[100] = ""; // Variable to hold extracted city value
    char region[100] = ""; // Variable to hold extracted region value
    char country[100] = ""; // Variable to hold extracted country value
    char org[150] = ""; // Variable to hold extracted organization value
    char loc[100] = ""; // Variable to hold extracted coordinates value


    // ------------------------------------------------------------
    // INPUT SECTION
    // ------------------------------------------------------------

    printf("=== GeoLocator (IP Address Lookup) ===\n\n"); // Display program title
    printf("Enter an IP address (e.g., 8.8.8.8): "); // Prompt user for IP address
    scanf("%99s", ipAddress); // Read IP address input from user (limit input to 99 chars)
    printf("\n"); // Print a blank line for spacing

    // Validate that something was entered
    if (strlen(ipAddress) < 3) // If user entered nothing or too short
    {
        printf("Error: Invalid IP address input.\n"); // Display error message
        return 1; // Exit program with error code
    }

    // ------------------------------------------------------------
    // PROCESSING SECTION
    // ------------------------------------------------------------

    int result = get_geo_info(ipAddress, city, region, country, org, loc);

    if (result != 0)
    {
        printf("Error: Failed to retrieve or parse IP data.\n");
        return 1;
    }

    // ------------------------------------------------------------
    // OUTPUT SECTION
    // ------------------------------------------------------------

    printf("=== GeoLocator Results ===\n"); // Print output header
    printf("City: %s\n", strlen(city) ? city : "N/A"); // Display city or N/A if missing
    printf("Region: %s\n", strlen(region) ? region : "N/A"); // Display region or N/A
    printf("Country: %s\n", strlen(country) ? country : "N/A"); // Display country or N/A
    printf("Organization: %s\n", strlen(org) ? org : "N/A"); // Display organization or N/A
    printf("Coordinates: %s\n", strlen(loc) ? loc : "N/A"); // Display coordinates or N/A
    printf("\nLookup complete.\n"); // Notify user of completion

    return 0; // Indicate successful program termination
} // end main()
