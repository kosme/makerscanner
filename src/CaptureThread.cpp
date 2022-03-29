/*
* Copyright 2009-2010, Andrew Barry
*
* This file is part of MakerScanner.
*
* MakerScanner is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License (Version 2, June 1991) as published by
* the Free Software Foundation.
*
* MakerScanner is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "CaptureThread.h"

wxDEFINE_EVENT(IMAGE_UPDATE_EVENT, wxCommandEvent);

CaptureThread::CaptureThread(wxFrame *windowIn, cv::VideoCapture *captureIn) : wxThread(wxTHREAD_JOINABLE)
{
    currentCaptureStatus = IDLE;
    window = windowIn;
    cvCapture = captureIn;
    src = new cv::Mat();
    //pDstImg = new cv::Mat();
}

// called on thread quit -- free all memory
void CaptureThread::OnExit()
{

  while (!imageQueue.empty()) {
    cv::Mat *image = imageQueue.front();
    imageQueue.pop();
    image->~Mat();
    //wxDELETE(image);
  }
  src->~Mat();
  delete src;
  cvCapture->~VideoCapture();
  window = nullptr;
}

// Called when thread is started
void* CaptureThread::Entry()
{
    while (true)
    {
        // check to see if the thread should exit
        if (TestDestroy() == true)
        {
            break;
        }

        if (currentCaptureStatus == ACTIVE)
        {
            // get a new image
            CaptureFrame();
        } else if (currentCaptureStatus == PREVIEW)
        {

            // get a new image and show it on screen
            CaptureFrame();
            SendFrame(imageQueue.back());
        } else if (currentCaptureStatus == IDLE)
        {
            Sleep(10);
        } else if (currentCaptureStatus == STOP)
        {
            break;
        }

        Yield();
    }

    return NULL;
}

void CaptureThread::CaptureFrame()
{   
    if (!cvCapture){
        //fail
        return;
    }

    if (imageQueue.size() > 100)
    {
        // stack too big, throw out some data
        imageQueue.pop();
    }

    for (int i=0; i < 1; i++) {
        cvCapture->read(*src); // it takes a few images to get to the newest one???
    }
    //cv::imshow("My Camera", src); cv::waitKey(25);
    imageQueue.push(src);
}

cv::Mat* CaptureThread::Pop()
{
    if (imageQueue.size() <= 0)
    {
        CaptureFrame();
    }

    cv::Mat *image = imageQueue.front();

    if (imageQueue.size() > 1)
    {
        imageQueue.pop();
    }

    return image;
}

/*
* Flush the stack, allowing the user to make sure s/he gets the most
* up to date image.  Delete all images in the stack.
*/
void CaptureThread::Flush()
{
    CaptureStatus oldStatus = currentCaptureStatus;

    currentCaptureStatus = IDLE;

    while (imageQueue.size() > 0)
    {
        imageQueue.pop();

        // since you should never release an image gotten by cvRetrieveFrame,
        // we don't need to release images here.
    }

    currentCaptureStatus = oldStatus;
}

// Display the given image on the frame
// Copies the image so it is safe to change it after the function call
void CaptureThread::SendFrame(cv::Mat *frame)
{
    if (!frame)
    {
        return;
    }

    cv::Size sz = cv::Size(frame->cols, frame->rows);
    pDstImg = new cv::Mat(sz, CV_8UC3, cv::Scalar::all(0));

    // convert the image into a 3 channel image for display on the frame
    if (frame->type() == CV_8UC1)
    {
        // Convert grayscale to RGB
        // cvCvtColor(frame, pDstImg, CV_GRAY2BGR);

        cv::cvtColor(*frame, *pDstImg, cv::COLOR_GRAY2BGR);
    } else if (frame->type() == CV_8UC3){

        // opencv stores images as BGR instead of RGB so we need to convert
        cv::cvtColor(*frame, *pDstImg, cv::COLOR_RGB2BGR);

    } else {
        // we don't know how to display this image based on its number of channels

        // give up
        delete pDstImg;
        return;
    }

    wxCommandEvent event(IMAGE_UPDATE_EVENT, GetId());

    // send the image in the event
    event.SetClientData(pDstImg);

    // Send the event to the frame!
    window->GetEventHandler()->AddPendingEvent(event);
}
