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

int main(void) // Main function where program execution begins
{

    // ------------------------------------------------------------
    // Constant and Variable Declarations
    // ------------------------------------------------------------

    const int MAX_URL_LENGTH = 256; // Maximum length for URL strings
    const int MAX_LINE_LENGTH = 512; // Maximum length for lines read from file
    const char TEMP_FILE[] = "geo_temp.json"; // Temporary file name for API response

    char ipAddress[100] = ""; // Variable to store user input for IP address
    char url[MAX_URL_LENGTH]; // Variable to hold constructed API URL
    char command[MAX_URL_LENGTH + 50]; // Variable to build curl command
    char line[MAX_LINE_LENGTH]; // Variable to hold each line read from JSON file

    char city[100] = ""; // Variable to hold extracted city value
    char region[100] = ""; // Variable to hold extracted region value
    char country[100] = ""; // Variable to hold extracted country value
    char org[150] = ""; // Variable to hold extracted organization value
    char loc[100] = ""; // Variable to hold extracted coordinates value

    FILE *filePtr = NULL; // File pointer for reading curl output


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

    // Build the request URL using user input
    snprintf(url, sizeof(url), "https://ipinfo.io/%s/json", ipAddress); // Construct URL for ipinfo.io API

    // Build the curl command to silently fetch JSON and save it to a temp file
    snprintf(command, sizeof(command), "curl -s %s -o %s", url, TEMP_FILE); // Construct full shell command

    // Execute the curl command
    int curlStatus = system(command); // Run the curl command in the shell

    // Check if curl command failed to execute properly
    if (curlStatus != 0) // If curl returns a nonzero exit code
    {
        printf("Error: Failed to retrieve data. Please check your internet connection.\n"); // Print network error
        return 1; // Exit program
    }

    // Open the temporary file created by curl
    filePtr = fopen(TEMP_FILE, "r"); // Open file in read mode
    if (filePtr == NULL) // If file could not be opened
    {
        printf("Error: Could not open response file.\n"); // Display error message
        return 1; // Exit program
    }

    // Read through file and extract JSON key-value pairs
    while (fgets(line, sizeof(line), filePtr)) // Read one line at a time
    {
        if (strstr(line, "\"city\"")) // If line contains "city"
        {
            sscanf(line, " \"city\": \"%[^\"]\"", city); // Extract city value
        }
        else if (strstr(line, "\"region\"")) // If line contains "region"
        {
            sscanf(line, " \"region\": \"%[^\"]\"", region); // Extract region value
        }
        else if (strstr(line, "\"country\"")) // If line contains "country"
        {
            sscanf(line, " \"country\": \"%[^\"]\"", country); // Extract country value
        }
        else if (strstr(line, "\"org\"")) // If line contains "org"
        {
            sscanf(line, " \"org\": \"%[^\"]\"", org); // Extract organization value
        }
        else if (strstr(line, "\"loc\"")) // If line contains "loc"
        {
            sscanf(line, " \"loc\": \"%[^\"]\"", loc); // Extract coordinates value
        }
        else if (strstr(line, "\"error\"")) // If line contains an "error" field (invalid IP)
        {
            printf("Error: Invalid or unreachable IP address.\n"); // Print API error message
            fclose(filePtr); // Close the file
            remove(TEMP_FILE); // Delete temp file
            return 1; // Exit program
        }
    }

    fclose(filePtr); // Close the file after reading


    // ------------------------------------------------------------
    // ERROR HANDLING SECTION
    // ------------------------------------------------------------

    // If all key fields are empty, it likely failed or was invalid
    if (strlen(city) == 0 && strlen(region) == 0 &&
        strlen(country) == 0 && strlen(org) == 0 && strlen(loc) == 0)
    {
        printf("Error: No valid data returned. The IP may be unreachable or invalid.\n"); // Show data error
        remove(TEMP_FILE); // Delete the temporary file
        return 1; // Exit with error
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

    // Remove the temporary file to clean up
    remove(TEMP_FILE); // Delete the curl output file

    return 0; // Indicate successful program termination
} // end main()



