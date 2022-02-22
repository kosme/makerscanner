#ifndef DISTANCETOREFERENCEDIALOG_H
#define DISTANCETOREFERENCEDIALOG_H

//(*Headers(DistanceToReferenceDialog)
#include <wx/spinctrl.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/stattext.h>
//*)

#define USER_CENTERED_LASER 999

#include "CaptureThread.h"

class DistanceToReferenceDialog: public wxDialog
{
	public:

		DistanceToReferenceDialog(CaptureThread *captureThreadIn, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DistanceToReferenceDialog();

		//(*Declarations(DistanceToReferenceDialog)
		wxPanel* Panel1;
		wxButton* btnLaserCentered;
		wxStaticText* lblOr;
		wxStaticText* lblCoverLaser;
		wxStaticText* StaticText1;
		wxStaticLine* StaticLine1;
		wxButton* btnLaserCovered;
		wxStaticText* lblCenterLaser;
		wxStaticText* lblEnterDistance;
		wxSpinCtrl* spinDistance;
		wxButton* btnDistanceEntered;
		//*)

		float GetWallDistance() { return distance; }
		cv::Mat* GetLaserCenteredImage() { return laserCentered; }
		cv::Mat* GetNoLaserImage() { return noLaserImage; }

		virtual bool TransferDataFromWindow();

	protected:

		//(*Identifiers(DistanceToReferenceDialog)
		static const long ID_STATICTEXT1;
		static const long ID_STATICLINE1;
		static const long ID_STATICTEXT4;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT5;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_SPINCTRL1;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(DistanceToReferenceDialog)
		void OnBtnLaserCenteredClick(wxCommandEvent& event);
		void OnBtnLaserCoveredClick(wxCommandEvent& event);
		//*)

		float distance;
		cv::Mat *noLaserImage, *laserCentered;
		CaptureThread *captureThread;

		DECLARE_EVENT_TABLE()
};

#endif
