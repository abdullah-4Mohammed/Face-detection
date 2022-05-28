# Face-detection
--------    Basic image processing && Face detecting using OPENCV Librarey  ----------
--------                         Abdullah A. Mohammed                       ----------
--------                https://github.com/abdullah-4Mohammed               ----------
--------      https://www.linkedin.com/in/abdullah-a-mohammed-94114388/     ----------


This file include explanations ofFace detection &amp;&amp; Basic image processing using C++ OPENCV Library
 - program code.
I will try to explain the uncleared points in the code. I have started the
code by separating the required tasks. case switching statement is used to
control this separation based on what the user chose through the
interactive statement.
_________________________
The smoothing:
case 'm':
medianBlur( frame, proce_1, 5 );
medianBlur( frame, proce_1, 31 );
I have used Medianblur function for smoothing operation. this algorithm
work by replacing the value of each pixel by the average of all the pixels
values around him in a squared window specified by the window size. then
this window scan all the image. by this the noise will decreased as well as
any sharp changing in the image because it will be spread on the
neighbors values. and this effect will increase as the window size
increased.
To show the effect effect of the window size, I have made two window
sizes, one with size 5x5 and the other with 31x31. where we will see that
at size 5x5 the image got a good smoothing where at 31x31 the edges in
the image start to be disappeared and the image looks like milted.
In Opencv examples, they recommended window size 3x3. However, I
found size 5x5 much better.Edge detection:
case 'e':
minMaxLoc(proce_1, &m, &M, &p_min, &p_max);
cout << "min: " << m << " at " << p_min << endl;
cout << "max: " << M << " at " << p_max << endl << endl ;
Canny(proce_1, proce_2, 0.12*M, 0.35*M, 3);
Canny(proce_1, proce_2, 100, 200, 3);
I used canny function for edge detection. canny algorithm use two
threshold to detect the edges. based on the minimum and maximum
threshold the pixel value will be classified as a part of edge or not. The
examples in the Opencv documents use values 100 and 200 as min and
max threshold respectively. this values based on canny recommendations
as min:max = 1:2 or 1:3. I tried to make the min and max threshold
depend on the image state. To make this dependency, I find the pixel with
the maximum value and the one with the minimum value and their
locations.
I made the min and max threshold as a ratio of the maximum pixel value.
Actually this method be more effective in the low light cases where the
maximum pixel value about 175. it shows good efficiency comparing with
the fixed value dependency method.
I tried to feed the min and max threshold from the threshold of
adaptive_threshold function but I failed. It take threshold based on the
maximum pixel value at a specific window not all the image and I think it
will be more efficient.
I avoided using “Trackbar” method to show the image as in opencv
document because it will capture one frame only. The “Trackbar” will call
canny function each time the slide changed and thus a new frame will be
processed because we taking a real time stream so the comparing will not
be efficient.Thresholding:
case 't' :
adaptiveThreshold(proce_1, proce_2, 125, 1 , 1 , 5, 5);
adaptiveThreshold(proce_1, proce_2, 255, 1 , 1 , 555, 5);
threshold( proce_1, proce_2, 127,255, 1 );
//threshold( src_gray, dst, threshold_value,
max_BINARY_value,threshold_type );
//adaptiveThreshold(src, dst, maxValue, adaptiveMethod, thresholdType,
blockSize, C);
Opencv ofter two functions to make thresholding: the simple one and the
adaptive one.
the difference between them is that the simple depend on a fixed values
where the adaptive use the maximum pixel value in a specified window
and used it to specify the value of the threshold. pixels with values more
than the threshold will be replaced to the value specified by
"max_BINARY_value" and "maxValue" fields in both of them, I used 255 as
white color.
I used binary inverse where I want to see the image as negative image.
The threshold_type vary from 0 - 4.
cv.THRESH_BINARY = 0.
cv.THRESH_BINARY_INV = 1.
cv.THRESH_TRUNC = 2
cv.THRESH_TOZERO = 3
cv.THRESH_TOZERO_INV = 4
adaptiveMethod
ADAPTIVE_THRESH_MEAN_C = 0.
ADAPTIVE_THRESH_GAUSSIAN_C =1.
The adaptive function because it use window to scan the image so when
the window size small it works like edge detector because it effect on a
small window and the threshold vale within that window only. I tried tomake two widow size to show that as the widow become big as the
adaptive start approach from the simple edge detection function.
Face detecting:
case 'f' :
cvtColor(frame, proce_1, CV_BGR2GRAY);
equalizeHist( proce_1, proce_1 );
medianBlur( proce_1, proce_1, 5 );
face_cascade.detectMultiScale( proce_1, faces, 1.1, 3, 0|
CV_HAAR_SCALE_IMAGE, Size(55, 55) );
I found making some smoothing make the face detection more efficient
and eliminate the noise that can make the algorithm consider them as an
objects of face and make falls decisions.
Opencv documentation recommended the minimum possible object size to
be 30x30 for the multi-scale classifier. Any object less than this will be
ignored. however, I used window 55x55 which I found it more better to
ignore many noise that the algorithm make falls decision of them. with
minimum size 55x55, still the algorithm can detect the faces from distance
5 miters of my laptop web-cam "5 M pixel".
Destroying the windows:
destroyAllWindows();
I used this function to destroy all the open windows where it is better than
issuing destroy function for each window separately. Another reason, I
don’t know which window will be open and which are not where it
depends on the user choice.
I found that it is not necessary to issue window destroying where without
this command still the windows are terminated as the program
terminated. "imageshow" still showing the image without initializing awindow. without initializing window, the image window will not be able to
resized.
