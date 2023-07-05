# Document-Scanner
This document scanner program, implemented using C++ and the OpenCV library, showcases image processing skills by detecting and extracting documents from images or live video feed.

This C++ program performs image preprocessing, detects the document's contour points, applies a perspective transformation to obtain a top-down view, and crops the image. The program allows for scanning documents from either a live video feed or an image file, providing document scanning tasks.


**Installation**

Clone the repository:
Navigate to the project directory:
g++ main.cpp -o DocumentScanner -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect


**Usage**

Run the program, and it will display a window showing the captured or loaded image.

_If using a webcam:_

Press the 'Enter' key to capture an image from the webcam.
Press the 'Esc' key to exit the program.

_If loading an image file:
_
Provide the path to the image file in the path variable in the main() function.
The program will automatically load the image and proceed to the next steps.

The program will process the image by detecting edges, identifying the document contour, and applying perspective transformation.

The program will display the original image, the preprocessed image with detected edges, and the transformed document image.

Press any key to save the transformed document image to the disk.

**Contribution**

Contributions to the Document Scanner project are welcome. Feel free to fork the repository and submit pull requests with your improvements.

If you find any issues or have suggestions for enhancements, please create an issue in the GitHub repository.

**Acknowledgments**

The Document Scanner project demonstrates the capabilities of OpenCV for image processing and perspective transformation. It provides a simple and efficient way to extract document regions from images for further analysis or processing.


Here is the result
![image](https://github.com/VardanKeshishyan/Document-Scanner/assets/138354187/fb6f0977-0c29-434d-a943-7ba5f66eda14)
