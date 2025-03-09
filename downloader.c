//The code is an example of a webscarper using curl library in C
//A non-existing website of address: https://backend.com/assets/img/private_album/role1319/album%d/%d.jpeg is used
//The website has a syncronized url adressing each image in jpeg format
//An album or role is skipped if non-existant url or error is found i.e of a certain value exceeds

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Function to download a file from a URL
int download_file(const char *url, const char *output_path) {
    CURL *curl;
    CURLcode res;

    FILE *file = fopen(output_path, "wb");
    if (!file) {
        printf("Error: Could not open file %s for writing.\n", output_path);
        return 0;
    }

    curl = curl_easy_init();
    if (!curl) {
        printf("Error: Could not initialize curl.\n");
        fclose(file);
        return 0;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L); // Treat HTTP errors as failures

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("Failed to download %s: %s\n", url, curl_easy_strerror(res));
        fclose(file);
        curl_easy_cleanup(curl);
        return 0;
    }

    fclose(file);
    curl_easy_cleanup(curl);
    return 1;
}

// Main function to scrape and download 100 pictures
void scrape_and_download(const char *base_url, int max_albums, int max_images, const char *output_dir, int max_fails) {
    char url[512], output_path[512];
    int count = 0, fail_count = 0;

    // Make sure the directory exists
    char mkdir_command[256];
    snprintf(mkdir_command, sizeof(mkdir_command), "mkdir -p %s", output_dir);
    system(mkdir_command);

    for (int album = 1; album <= max_albums && count < 100 && fail_count < max_fails; album++) {
        for (int img = 1; img <= max_images && count < 100 && fail_count < max_fails; img++) {
            snprintf(url, sizeof(url), base_url, album, img);
            snprintf(output_path, sizeof(output_path), "%s/image_%03d.jpeg", output_dir, count + 1);

            printf("Downloading: %s\n", url);
            if (download_file(url, output_path)) {
                printf("Saved to: %s\n", output_path);
                count++;
                fail_count = 0;  // Reset fail count on success
            } else {
                fail_count++;  // Increment fail count
                printf("Failed to download %s\n", url);
            }
        }
    }

    if (fail_count >= max_fails) {
        printf("Stopping download after %d consecutive failures.\n", max_fails);
    } else {
        printf("Downloaded %d pictures.\n", count);
    }
}

int main() {
    // Define the URL pattern
    const char *base_url = "https://backend.com/assets/img/private_album/role1319/album%d/%d.jpeg"; //any data type can be used in place of %d like %s , %f, %c

    // Parameters for albums and images
    int max_albums = 10;  // Maximum number of albums to scan
    int max_images = 20;  // Maximum number of images per album

    // Specify the desired folder path for downloads
    const char *output_dir = "/home/";  // Replace with your desired path

    // Maximum number of consecutive failed downloads before stopping
    int max_fails = 10;  // You can adjust this as needed

    // Scrape and download the pictures
    scrape_and_download(base_url, max_albums, max_images, output_dir, max_fails);

    return 0;
}
