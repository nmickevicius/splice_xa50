// --------------------------------------------------------------------------------
//   Copyright (C) Siemens Healthcare GmbH, 2015-2018. All Rights Reserved. Confidential.
// --------------------------------------------------------------------------------
//
//  \file  MrImagingFW\seq\a_MiniFLASH\a_MiniFLASH_UI.h
//
//  \brief File containing declaration of the UI class
///          - MiniFlashUI
///
///  This file contains the implementation of the class MiniFlashUI.
///  The sequence a_MiniFlash use it to generate very nice images.
///
//     Remarks: This is the demo sequence MiniFLASH.
//              DO NOT base any diagnosis on images generated by this sequence.
///
//    -----------------------------------------------------------------------------

#pragma once

#ifndef a_MiniFLASH_UI_h
#define a_MiniFLASH_UI_h

//  -------------------------------------------------------------------------- *
//  Application includes                                                       *
//  -------------------------------------------------------------------------- *
#include <a_MiniFLASH.h>

#include <MrImagingFW/WIPParameterTool/WIPParameterTool.h>

//  -------------------------------------------------------------------------- *
//  Forward declarations                                                       *
//  -------------------------------------------------------------------------- *
class MrProt;
class SeqLim;
class SeqExpo;
class Sequence;

namespace SEQ_NAMESPACE
{
//  --------------------------------------------------------------------------
//
//  Name        : MiniFlashUI
//
//  Description :
/// \brief        This class basically is a storage for the pointers to the
///               original setValue / getValue / solve - handlers.
///
///               The sequence registers new UI handlers, which usually do
///               something, call the original UI handler, and then
///               do something else. To keep the information of the original
///               UI handlers, the MiniFlashUI class stores the pointers.
///
///               It also provides the method registerUI to execute the
///               registration of all new handlers (and the storage of
///               the original pointers)
///
//  --------------------------------------------------------------------------

class MiniFlashUI : public SequenceUI<MiniFlash>
{
  public:
    //  --------------------------------------------------------------
    //
    //  Name        :  MiniFlashUI::MiniFlashUI
    //
    //  Description :
    /// \brief         Initialization of class members
    //
    //  Return      :
    //
    //  --------------------------------------------------------------
    MiniFlashUI() = default;

    //  --------------------------------------------------------------
    //
    //  Name        :  MiniFlashUI::~MiniFlashUI
    //
    //  Description :
    /// \brief         Destructor
    //
    //  Return      :
    //
    //  --------------------------------------------------------------
    virtual ~MiniFlashUI() = default;

    //  --------------------------------------------------------------------------
    //
    //  Name        : MiniFlashUI::registerUI
    //
    //  Description :
    /// \brief        This function initializes the UI functions and
    ///               registers all given set / get / Solve - handlers
    ///
    ///               It can be executed on the measurement system, too, but is empty there.
    ///
    ///               On the host, it executes these steps:
    ///               - Declaration of pointers to UI classes
    ///               - Registration of overloaded set value handlers
    ///
    ///               It returns an NLS status
    ///
    NLS_STATUS registerUI(SeqLim& rSeqLim, WPT_NAMESPACE::WIPParameterTool& rTool);

}; // end of class MiniFlashUI
}; // end of namespace SEQ_NAMESPACE

#endif // end of ifndef a_MiniFLASH_UI_h
