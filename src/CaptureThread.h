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

#ifndef CAPTURE_THREAD_H
#define CAPTURE_THREAD_H

#include <wx/wx.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include <queue>

using namespace std;

/*
* IDLE = don't capture, but stay alive
* CAPTURE = Try to get every frame, enabling a limited-size buffer
* PREVIEW = Get frames and immediatley send them to the frame via events
* STOP = Leave the thread loop.  Set this right before you Wait() for the thread to exit.
*/
enum CaptureStatus
{
	IDLE,
	ACTIVE,
	PREVIEW,
	STOP
};

BEGIN_DECLARE_EVENT_TYPES()
  wxDECLARE_EVENT(IMAGE_UPDATE_EVENT, wxCommandEvent);
END_DECLARE_EVENT_TYPES()


class CaptureThread : public wxThread
{
	public:
		// Constructor
		CaptureThread(wxFrame *windowIn, cv::VideoCapture *captureIn);

		// Function that is run on thread init
		virtual void* Entry();

		// Safely close
		virtual void OnExit();

		cv::Mat* Pop();

		void SetCapture(CaptureStatus newStatus) { currentCaptureStatus = newStatus; }

		int GetQueueSize() { return imageQueue.size(); }
		void SendFrame(cv::Mat *frame);

		void Flush();

	private:

		CaptureStatus currentCaptureStatus;

		wxFrame *window;
		cv::VideoCapture *cvCapture;

		void CaptureFrame();

		queue<cv::Mat*> imageQueue;

    cv::Mat *src;

    cv::Mat *pDstImg;
};



#endif //CAPTURE_THREAD_H
