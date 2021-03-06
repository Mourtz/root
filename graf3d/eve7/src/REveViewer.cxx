// @(#)root/eve:$Id$
// Authors: Matevz Tadel & Alja Mrak-Tadel: 2006, 2007

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#include <ROOT/REveViewer.hxx>

#include <ROOT/REveScene.hxx>
#include <ROOT/REveSceneInfo.hxx>
#include <ROOT/REveManager.hxx>
#include <ROOT/REveSelection.hxx>

#include "TApplication.h"
#include "TEnv.h"
#include "TSystem.h"

using namespace ROOT::Experimental;
namespace REX = ROOT::Experimental;

/** \class REveViewer
\ingroup REve
Eve representation of a GL view. In a gist, it's a camera + a list of scenes.

*/

////////////////////////////////////////////////////////////////////////////////
/// Constructor.

REveViewer::REveViewer(const char* n, const char* t) :
   REveElementList(n, t)
{
   // SetChildClass(REveSceneInfo::Class());
}

////////////////////////////////////////////////////////////////////////////////
/// Destructor.

REveViewer::~REveViewer()
{}

////////////////////////////////////////////////////////////////////////////////
/// Redraw viewer immediately.

void REveViewer::Redraw(Bool_t /*resetCameras*/)
{
   // if (resetCameras) fGLViewer->PostSceneBuildSetup(kTRUE);
   // fGLViewer->RequestDraw(TGLRnrCtx::kLODHigh);
}

////////////////////////////////////////////////////////////////////////////////
/// Add 'scene' to the list of scenes.

void REveViewer::AddScene(REveScene* scene)
{
   static const REveException eh("REveViewer::AddScene ");

   for (auto i = BeginChildren(); i != EndChildren(); ++i)
   {
      auto sinfo = dynamic_cast<REveSceneInfo*>(*i);

      if (sinfo && sinfo->GetScene() == scene)
      {
         throw eh + "scene already in the viewer.";
      }
   }

   REveSceneInfo* si = new REveSceneInfo(this, scene);
   AddElement(si);
}

////////////////////////////////////////////////////////////////////////////////
/// Remove element 'el' from the list of children and also remove
/// appropriate GLScene from GLViewer's list of scenes.
/// Virtual from REveElement.

void REveViewer::RemoveElementLocal(REveElement* /*el*/)
{
   // fGLViewer->RemoveScene(((REveSceneInfo*)el)->GetGLScene());

   // XXXXX Notify clients !!! Or will this be automatic?
}

////////////////////////////////////////////////////////////////////////////////
/// Remove all children, forwarded to GLViewer.
/// Virtual from REveElement.

void REveViewer::RemoveElementsLocal()
{
   // fGLViewer->RemoveAllScenes();

   // XXXXX Notify clients !!! Or will this be automatic?
}

////////////////////////////////////////////////////////////////////////////////
/// Object to be edited when this is selected, returns the TGLViewer.
/// Virtual from REveElement.

TObject* REveViewer::GetEditorObject(const REveException& /*eh*/) const
{
   // if (!fGLViewer)
   //    throw(eh + "fGLViewer not set.");
   // return fGLViewer;

   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Receive a pasted object. REveViewer only accepts objects of
/// class REveScene.
/// Virtual from REveElement.

Bool_t REveViewer::HandleElementPaste(REveElement* el)
{
   static const REveException eh("REveViewer::HandleElementPaste ");

   REveScene* scene = dynamic_cast<REveScene*>(el);
   if (scene != 0) {
      AddScene(scene);
      return kTRUE;
   } else {
      Warning(eh.Data(), "class REveViewer only accepts REveScene paste argument.");
      return kFALSE;
   }
}


/** \class REveViewerList
\ingroup REve
List of Viewers providing common operations on REveViewer collections.
*/

////////////////////////////////////////////////////////////////////////////////

REveViewerList::REveViewerList(const char* n, const char* t) :
   REveElementList(n, t),
   fShowTooltip   (kTRUE),

   fBrightness(0),
   fUseLightColorSet(kFALSE)
{
   // Constructor.

   SetChildClass(REveViewer::Class());
   Connect();
}

////////////////////////////////////////////////////////////////////////////////
/// Destructor.

REveViewerList::~REveViewerList()
{
   Disconnect();
}

////////////////////////////////////////////////////////////////////////////////
/// Call base-class implementation.
/// If compound is open and compound of the new element is not set,
/// the el's compound is set to this.

void REveViewerList::AddElement(REveElement* el)
{
   REveElementList::AddElement(el);
   el->IncParentIgnoreCnt();
}

////////////////////////////////////////////////////////////////////////////////
/// Decompoundofy el, call base-class version.

void REveViewerList::RemoveElementLocal(REveElement* el)
{
   // This was needed as viewer was in EveWindowManager hierarchy, too.
   // el->DecParentIgnoreCnt();

   REveElementList::RemoveElementLocal(el);
}

////////////////////////////////////////////////////////////////////////////////
/// Decompoundofy children, call base-class version.

void REveViewerList::RemoveElementsLocal()
{
   // This was needed as viewer was in EveWindowManager hierarchy, too.
   // el->DecParentIgnoreCnt();
   // for (List_i i=fChildren.begin(); i!=fChildren.end(); ++i)
   // {
   //    (*i)->DecParentIgnoreCnt();
   // }

   REveElementList::RemoveElementsLocal();
}

////////////////////////////////////////////////////////////////////////////////
/// Connect to TGLViewer class-signals.

void REveViewerList::Connect()
{
   // TQObject::Connect("TGLViewer", "MouseOver(TObject*,UInt_t)",
   //                   "REveViewerList", this, "OnMouseOver(TObject*,UInt_t)");

   // TQObject::Connect("TGLViewer", "ReMouseOver(TObject*,UInt_t)",
   //                   "REveViewerList", this, "OnReMouseOver(TObject*,UInt_t)");

   // TQObject::Connect("TGLViewer", "UnMouseOver(TObject*,UInt_t)",
   //                   "REveViewerList", this, "OnUnMouseOver(TObject*,UInt_t)");

   // TQObject::Connect("TGLViewer", "Clicked(TObject*,UInt_t,UInt_t)",
   //                   "REveViewerList", this, "OnClicked(TObject*,UInt_t,UInt_t)");

   // TQObject::Connect("TGLViewer", "ReClicked(TObject*,UInt_t,UInt_t)",
   //                   "REveViewerList", this, "OnReClicked(TObject*,UInt_t,UInt_t)");

   // TQObject::Connect("TGLViewer", "UnClicked(TObject*,UInt_t,UInt_t)",
   //                   "REveViewerList", this, "OnUnClicked(TObject*,UInt_t,UInt_t)");
}

////////////////////////////////////////////////////////////////////////////////
/// Disconnect from TGLViewer class-signals.

void REveViewerList::Disconnect()
{
   // TQObject::Disconnect("TGLViewer", "MouseOver(TObject*,UInt_t)",
   //                      this, "OnMouseOver(TObject*,UInt_t)");

   // TQObject::Disconnect("TGLViewer", "ReMouseOver(TObject*,UInt_t)",
   //                      this, "OnReMouseOver(TObject*,UInt_t)");

   // TQObject::Disconnect("TGLViewer", "UnMouseOver(TObject*,UInt_t)",
   //                      this, "OnUnMouseOver(TObject*,UInt_t)");

   // TQObject::Disconnect("TGLViewer", "Clicked(TObject*,UInt_t,UInt_t)",
   //                      this, "OnClicked(TObject*,UInt_t,UInt_t)");

   // TQObject::Disconnect("TGLViewer", "ReClicked(TObject*,UInt_t,UInt_t)",
   //                      this, "OnReClicked(TObject*,UInt_t,UInt_t)");

   // TQObject::Disconnect("TGLViewer", "UnClicked(TObject*,UInt_t,UInt_t)",
   //                      this, "OnUnClicked(TObject*,UInt_t,UInt_t)");
}

////////////////////////////////////////////////////////////////////////////////
/// Repaint viewers that are tagged as changed.

void REveViewerList::RepaintChangedViewers(Bool_t /*resetCameras*/, Bool_t /*dropLogicals*/)
{
   for (List_i i=fChildren.begin(); i!=fChildren.end(); ++i)
   {
      // TGLViewer* glv = ((REveViewer*)*i)->GetGLViewer();
      // if (glv->IsChanged())
      // {
      //    if (resetCameras) glv->PostSceneBuildSetup(kTRUE);
      //    if (dropLogicals) glv->SetSmartRefresh(kFALSE);

      //    glv->RequestDraw(TGLRnrCtx::kLODHigh);

      //    if (dropLogicals) glv->SetSmartRefresh(kTRUE);
      // }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Repaint all viewers.

void REveViewerList::RepaintAllViewers(Bool_t /*resetCameras*/, Bool_t /*dropLogicals*/)
{
   for (List_i i=fChildren.begin(); i!=fChildren.end(); ++i)
   {
      // TGLViewer* glv = ((REveViewer*)*i)->GetGLViewer();

      // if (resetCameras) glv->PostSceneBuildSetup(kTRUE);
      // if (dropLogicals) glv->SetSmartRefresh(kFALSE);

      // glv->RequestDraw(TGLRnrCtx::kLODHigh);

      // if (dropLogicals) glv->SetSmartRefresh(kTRUE);
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Delete annotations from all viewers.

void REveViewerList::DeleteAnnotations()
{
   for (List_i i=fChildren.begin(); i!=fChildren.end(); ++i)
   {
      // TGLViewer* glv = ((REveViewer*)*i)->GetGLViewer();
      // glv->DeleteOverlayAnnotations();
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Callback done from a REveScene destructor allowing proper
/// removal of the scene from affected viewers.

void REveViewerList::SceneDestructing(REveScene* scene)
{
   for (List_i i=fChildren.begin(); i!=fChildren.end(); ++i)
   {
      REveViewer* viewer = (REveViewer*) *i;
      List_i j = viewer->BeginChildren();
      while (j != viewer->EndChildren())
      {
         REveSceneInfo* sinfo = (REveSceneInfo*) *j;
         ++j;
         if (sinfo->GetScene() == scene)
            viewer->RemoveElement(sinfo);
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Show / hide tooltip for various MouseOver events.
/// Must be called from slots where sender is TGLEventHandler.

void REveViewerList::HandleTooltip()
{
   if (fShowTooltip)
   {
      // TGLViewer       *glw = dynamic_cast<TGLViewer*>((TQObject*) gTQSender);
      // TGLEventHandler *glh = (TGLEventHandler*) glw->GetEventHandler();
      // if (REX::gEve->GetHighlight()->NumChildren() == 1)
      // {
      //    TString title(REX::gEve->GetHighlight()->FirstChild()->GetHighlightTooltip());
      //    if ( ! title.IsNull())
      //       glh->TriggerTooltip(title);
      // }
      // else
      // {
      //    glh->RemoveTooltip();
      // }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Slot for global TGLViewer::MouseOver() signal.
///
/// The attempt is made to determine the REveElement being
/// represented by the physical shape and global highlight is updated
/// accordingly.
///
/// If REveElement::IsPickable() returns false, the element is not
/// highlighted.
///
/// Highlight is always in single-selection mode.

void REveViewerList::OnMouseOver(TObject *obj, UInt_t /*state*/)
{
   REveElement *el = dynamic_cast<REveElement*>(obj);
   if (el && !el->IsPickable())
      el = 0;

   // void *qsender = gTQSender;
   // REX::gEve->GetHighlight()->UserPickedElement(el, kFALSE);
   // gTQSender = qsender;

   HandleTooltip();
}

////////////////////////////////////////////////////////////////////////////////
/// Slot for global TGLViewer::ReMouseOver().
///
/// The obj is dyn-casted to the REveElement and global selection is
/// updated accordingly.
///
/// If REveElement::IsPickable() returns false, the element is not
/// selected.

void REveViewerList::OnReMouseOver(TObject *obj, UInt_t /*state*/)
{
   REveElement* el = dynamic_cast<REveElement*>(obj);
   if (el && !el->IsPickable())
      el = 0;

   // void *qsender = gTQSender;
   // REX::gEve->GetHighlight()->UserRePickedElement(el);
   // gTQSender = qsender;

   HandleTooltip();
}

////////////////////////////////////////////////////////////////////////////////
/// Slot for global TGLViewer::UnMouseOver().
///
/// The obj is dyn-casted to the REveElement and global selection is
/// updated accordingly.
///
/// If REveElement::IsPickable() returns false, the element is not
/// selected.

void REveViewerList::OnUnMouseOver(TObject *obj, UInt_t /*state*/)
{
   REveElement* el = dynamic_cast<REveElement*>(obj);
   if (el && !el->IsPickable())
      el = 0;

   // void *qsender = gTQSender;
   // REX::gEve->GetHighlight()->UserUnPickedElement(el);
   // gTQSender = qsender;

   HandleTooltip();
}

////////////////////////////////////////////////////////////////////////////////
/// Slot for global TGLViewer::Clicked().
///
/// The obj is dyn-casted to the REveElement and global selection is
/// updated accordingly.
///
/// If REveElement::IsPickable() returns false, the element is not
/// selected.

void REveViewerList::OnClicked(TObject *obj, UInt_t /*button*/, UInt_t state)
{
   REveElement* el = dynamic_cast<REveElement*>(obj);
   if (el && !el->IsPickable())
      el = 0;
   REX::gEve->GetSelection()->UserPickedElement(el, state & kKeyControlMask);
}

////////////////////////////////////////////////////////////////////////////////
/// Slot for global TGLViewer::ReClicked().
///
/// The obj is dyn-casted to the REveElement and global selection is
/// updated accordingly.
///
/// If REveElement::IsPickable() returns false, the element is not
/// selected.

void REveViewerList::OnReClicked(TObject *obj, UInt_t /*button*/, UInt_t /*state*/)
{
   REveElement* el = dynamic_cast<REveElement*>(obj);
   if (el && !el->IsPickable())
      el = 0;
   REX::gEve->GetSelection()->UserRePickedElement(el);
}

////////////////////////////////////////////////////////////////////////////////
/// Slot for global TGLViewer::UnClicked().
///
/// The obj is dyn-casted to the REveElement and global selection is
/// updated accordingly.
///
/// If REveElement::IsPickable() returns false, the element is not
/// selected.

void REveViewerList::OnUnClicked(TObject *obj, UInt_t /*button*/, UInt_t /*state*/)
{
   REveElement* el = dynamic_cast<REveElement*>(obj);
   if (el && !el->IsPickable())
      el = 0;
   REX::gEve->GetSelection()->UserUnPickedElement(el);
}

////////////////////////////////////////////////////////////////////////////////
/// Set color brightness.

void REveViewerList::SetColorBrightness(Float_t b)
{
   REveUtil::SetColorBrightness(b, 1);
}

////////////////////////////////////////////////////////////////////////////////
/// Switch background color.

void REveViewerList::SwitchColorSet()
{
   fUseLightColorSet = ! fUseLightColorSet;
   for (List_i i=fChildren.begin(); i!=fChildren.end(); ++i)
   {
      // TGLViewer* glv = ((REveViewer*)*i)->GetGLViewer();
      // if ( fUseLightColorSet)
      //    glv->UseLightColorSet();
      // else
      //    glv->UseDarkColorSet();

      // glv->RequestDraw(TGLRnrCtx::kLODHigh);
   }
}
