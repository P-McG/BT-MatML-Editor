#include "BT_MatML_Editor-Config.h"
#include "BT_MatML_App.h"
#include "GUI/BT_MatML_MaterialFrame.h"

using namespace bellshire;

IMPLEMENT_APP(BT_MatML_App); /*! As per wxWidget, IMPLEMENT_APP(appClass), which allows wxWidgets to dynamically create an instance of the application object at the appropriate point in wxWidgets initialization.*/

using std::cerr;
using std::endl;

// ----------------------------------------------------------------------------
// Resources
// ----------------------------------------------------------------------------

#include "../images/BT_MatML_Editor_32px.xpm"


BT_MatML_App::BT_MatML_App()
{
}

BT_MatML_App::~BT_MatML_App()
{
}

bool BT_MatML_App::OnInit()
{


	/*!Creation of the application's main MaterialFrame window*/
	MaterialFrame* materialframe = new	MaterialFrame((wxWindow*)NULL);

	materialframe->SetIcon(BT_MatML_Editor_32px_xpm);

    // Show the frame
	materialframe->SetAutoLayout(true);/*!Sets up the layout of the frame window*/
	materialframe->Show();/*!Show the frame window*/
	SetTopWindow( materialframe );/*!Sets the frame window as the top frame*/

	return true;
}

int BT_MatML_App::OnExit()
{
    return 1;
}



