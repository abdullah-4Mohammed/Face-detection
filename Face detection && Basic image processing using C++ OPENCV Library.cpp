/* 

--------    Basic image processing && Face detecting using OPENCV Librarey  ----------
--------                         Abdullah A. Mohammed                       ----------
--------                https://github.com/abdullah-4Mohammed               ----------
--------      https://www.linkedin.com/in/abdullah-a-mohammed-94114388/     ----------


*/


#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

    int main(void)

    {
	
    // opening the webcam to start capturing in realtime.
    VideoCapture capture(0);
    	
    // checking if the webcam have been open. if not, stop the programe and show error message.
	if (capture.isOpened() == false)
	{
		cerr << "Cannot capture images from the web camera ..." << endl;
		return -1;
	}

	
    // variable's definations:  
     
    //defineng some image containers of type Mat. one for the orginal frame "frame" and two
    //for the processing " proce_1 and proce_2" 
    // variables: "z" to control showing intractive text; "o" to control the case switching
    // "m" "M" "p_min" " p_max" to save the maximum and minimum pixl values and their 
    //locations; "faces" of type vector to save the the cordinates of the detected faces in
    //the image; "face_cascade" of type class to classify the objects in the image and detect 
    // the faces in it.
	Mat frame;
	Mat proce_1;
	Mat proce_2;   
	int z = 1;  char o;
    double m, M;
    Point p_min, p_max;
    vector<Rect> faces;
    CascadeClassifier face_cascade;


    // making for loop to continue capturing and processing until pressing any key.
	for (int keyCode = -1 ; keyCode < 0 ; )
	{

    // coping the captured frame to the container "frame"
		capture >> frame;

	// checking if the container got data.
	if (frame.empty() == true)
			break;
		
    //makeing control so the intractive text appeare one time only per the loop.
        if (z == 1) 
    {

    // showing an intractive text so the user can specify his choice.
    cout << "Please press a letter to specify the process on the captured streem: \n Press 'g' for grayscal. \n Press 'h' for normlized histugram. \n Press 'm' for smoothing. \n Press 'e' for edge detection. \n Press 't' for thresholding. \n Press 'f' for face detection. " << endl;
    
    // inputing the pressed charechter from the user and saving it in variabl "o".
    cin >> o;

    // changing the value of the showing text control so it will not be shown next cycles.
    z = 0;
    }

    //checking the inputed character to process the specified process.
        switch (o) 
    {
      
    //if the character was "g", start gray scal process.  
        case 'g':

    //changing the color of the captured frame stored in container "frame" to grayscale 
    //and save it in container "proce_1".
        cvtColor(frame, proce_1, CV_BGR2GRAY);
         
    //intializing windows to show the orginal and the processsed images and showing them.
        namedWindow("Original_w", CV_WINDOW_NORMAL);
	    namedWindow("Gray_w", CV_WINDOW_NORMAL);
       
        imshow("Original_w", frame);  
		imshow("Gray_w", proce_1); 
  
            break;


    //if the character was "h", start normlized histugram process.
        case 'h':

    //changing the color of the captured frame stored in container "frame" to grayscale 
    //and save it in container "proce_1". then making the normlized histogram and save it
    //in the "Proce_2" 
        cvtColor(frame, proce_1, CV_BGR2GRAY);
        equalizeHist( proce_1, proce_2 );

    //intializing windows to show the orginal and the processsed images and showing them.
        namedWindow("Original_w", CV_WINDOW_NORMAL);
	    namedWindow("Gray_w", CV_WINDOW_NORMAL);
        namedWindow("Hist_w", CV_WINDOW_NORMAL);

        imshow("Original_w", frame);  
		imshow("Gray_w", proce_1); 
        imshow("Hist_w", proce_2);
        
            break;


    //if the character was "m", start a smoothing process.
        case 'm':

    //making a smoothing to the orginal image by using medianblur algorithm whith 
    //window size (5x5) pixel. please check Exercise_1A.pdf file.
        medianBlur( frame, proce_1, 5 );

        namedWindow("Original_w", CV_WINDOW_NORMAL);
        namedWindow("Median_5x5_w", CV_WINDOW_NORMAL);
        imshow("Original_w", frame);
        imshow("Median_5x5_w", proce_1);

    //making a smoothing to the orginal image by using medianblur algorithm whith 
    //window size (31x31) pixel. please check Exercise_1A.pdf file.
        medianBlur( frame, proce_1, 31 );

        namedWindow("Median_31x31_w", CV_WINDOW_NORMAL);
        imshow("Median_31x31_w", proce_1);
        
            break;

    //if the character was "e", start edge detection process.
        case 'e':

    //changing the color of the captured frame stored in container "frame" to grayscale 
    //and save it in container "proce_1". then making smoothing and save it
    //in the "Proce_1" as updating.    
        cvtColor(frame, proce_1, CV_BGR2GRAY);
        medianBlur( proce_1, proce_1, 5 );

    //find the pixel with the maximum value and the one with minmum value and their
    //locations then print them on the screen. please check Exercise_1A.pdf file.
        minMaxLoc(proce_1, &m, &M, &p_min, &p_max);
        cout << "min: " << m << " at " << p_min << endl;
        cout << "max: " << M << " at " << p_max << endl << endl ;
   
    //using canny algorithm to detect the edges in the gray image and save it in the
    //"proce_2 . use minmum and maximum threshold based on the value of the pixel with
    //maximum value in the image. this method will be selfe adjusable. please check Exercise_1A.pdf file.
        Canny(proce_1, proce_2, 0.12*M, 0.35*M, 3);

        namedWindow("Original_w", CV_WINDOW_NORMAL);
        namedWindow("Edge_based_MaxPixelValue_w", CV_WINDOW_NORMAL);
        imshow("Original_w", frame);
        imshow("Edge_based_MaxPixelValue_w", proce_2);

    //using canny algorithm to detect the edges in the gray image and save it in the
    //"proce_2 . use minmum and maximum threshold based on fixed value. please check Exercise_1A.pdf file.
        Canny(proce_1, proce_2, 100, 200, 3);

        namedWindow("Edge_based_fixedValue_w", CV_WINDOW_NORMAL);
        imshow("Edge_based_fixedValue_w", proce_2);
        
            break;

    //if the character was "t", start threshold process.
        case 't' :

    //changing the color of the captured frame stored in container "frame" to grayscale 
    //and save it in container "proce_1". then making smoothing and save it
    //in the "Proce_1" as updating.
        cvtColor(frame, proce_1, CV_BGR2GRAY);
        medianBlur( proce_1, proce_1, 5 );


    //making thresholding to the smoothed gray image and save it in "proce_2". using
    //adaptive threshold algorithem whith "ADAPTIVE_THRESH_GAUSSIAN_C" as adaptive method,
    //"THRESH_BINARY_INV" as  threshold Type, window size 5x5 and subtracted constant
    //equal to 5. please check Exercise_1A.pdf file.
    //adaptiveThreshold(src, dst, maxValue, adaptiveMethod, thresholdType, blockSize, C)
        adaptiveThreshold(proce_1, proce_2, 125, 1 , 1 , 5, 5);


		namedWindow("Original_w", CV_WINDOW_NORMAL);
        namedWindow("Adaptive_thresh_gaussian_INV_5", CV_WINDOW_NORMAL);
        imshow("Original_w", frame);  
		imshow("Adaptive_thresh_gaussian_INV_5", proce_2);

        adaptiveThreshold(proce_1, proce_2, 255, 1 , 1 , 555, 5);
        
        namedWindow("Adaptive_thresh_gaussian_INV_555", CV_WINDOW_NORMAL); 
        imshow("Adaptive_thresh_gaussian_INV_555", proce_2);

    //making thresholding to the smoothed gray image and save it in "proce_2". using
    //simple threshold algorithem whith , "127" as threshold value, "255" the new value
    //for the pixels who their value are  more than the threshold value,
    //"THRESH_BINARY_INV" as  threshold Type. please check Exercise_1A.pdf file.
    //threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );
        threshold( proce_1, proce_2, 127,255, 1 );
		 
        namedWindow("Simple_threshold_function_INV", CV_WINDOW_NORMAL);
        imshow("Simple_threshold_function_INV", proce_2);

            break;

    //if the character was "f", start face detecting process.
        case 'f' :

    //changing the color of the captured frame stored in container "frame" to grayscale 
    //and save it in container "proce_1", making normlized histogram, then making
    //smoothing and save it in the "Proce_1" as updating. please check Exercise_1A.pdf file.
        cvtColor(frame, proce_1, CV_BGR2GRAY);
        equalizeHist( proce_1, proce_1 );
        medianBlur( proce_1, proce_1, 5 );

    // Loading Face detector cascade haarcascade_frontalface_alt2.xml file. please put the path
    // for the file where it is located in your pc. please check Exercise_1A.pdf file.
        face_cascade.load( "/home/moh/opencv/release/test/haarcascade_frontalface_alt2.xml" );
 
    // Detecting faces in the image stored in "proce_1" and save the cordinates in the
    //victor "faces". "1.1" as a parameter specifying how much the image size is reduced at
    //each image scale. "3" as min neighbors which is a parameter specifying how many
    //neighbors each candidate rectangle should have to retain it. minmum object size is 
    //" 55x55", object smollar than this limit will be ignored. 
    //detectMultiScale(const Mat& image, vector<Rect>& objects, double scaleFactor=1.1,
    //int minNeighbors=3, int flags=0, Size minSize=Size(), Size maxSize=Size())
        face_cascade.detectMultiScale( proce_1, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(55, 55) );
 
    // Draw circles on the detected faces in the image based on the cordinates stored
    //in the vector "faces". please check Exercise_1A.pdf file.
         for( int i = 0; i < faces.size(); i++ )
        {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        }

        namedWindow("face_detecting_haarcascade_w", CV_WINDOW_NORMAL);
        imshow("face_detecting_haarcascade_w", frame); 

            break;


    // any other character will exite.
        default:
 
            break;

    }
		
		
		 
    //checking if the user press any key to exit the loop.
		keyCode = waitKey(10) % 256;

	}


    //destroying the windows. please check Exercise_1A.pdf file.
        destroyAllWindows();

    
}
