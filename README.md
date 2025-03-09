# prab_scraper
# Image Downloader using cURL

This C program is a simple web scraper that downloads images from a structured URL using the cURL library. It scans multiple albums and images, downloading available images while skipping missing ones.

## Features
- Downloads images from a synchronized URL structure.
- Skips non-existent albums or images after a certain number of failures.
- Saves images sequentially in a specified directory.
- Uses `cURL` to handle HTTP requests.

## Requirements
- A C compiler (e.g., `gcc`).
- `libcurl` installed on your system.

### Installation (Linux)
1. Install `libcurl`:
   ```bash
   sudo apt update
   sudo apt install libcurl4-openssl-dev
2. Compile the program:
  `gcc downloader.c -o downloader -lcurl`

3. Customization
      Modify URL pattern: Update base_url in the main() function.  
      Change output directory: Update `output_dir` in main().  
      Adjust scanning limits:  
      max_albums controls how many albums to scan.  
      max_images controls the max images per album.  
      max_fails sets the limit of consecutive failures before stopping.  
##**Limitations**
  The program does not handle dynamic web pages or JavaScript-based content.  
  Only works with publicly accessible URLs.  

##**License**
This project is for educational purposes only. Modify and use at your own risk.  


Let me know if you want any modifications!


