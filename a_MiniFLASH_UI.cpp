// --------------------------------------------------------------------------------
//   Copyright (C) Siemens Healthcare GmbH, 2015-2018. All Rights Reserved. Confidential.
// --------------------------------------------------------------------------------
//
//  \file  MrImagingFW\seq\a_MiniFLASH\a_MiniFLASH_UI.cpp
//
//  \brief Declarations for a_MiniFLASH.cpp
//
//  --------------------------------------------------------------------------------

//  --------------------------------------------------------------------------
//  Application includes
//  --------------------------------------------------------------------------
#include "a_MiniFLASH_UI.h"
#include "MrProtSrv/Domain/CoreNative/MrWipMemBlock.h" // NJM

// --------------------------------------------------------------------------
// General Includes
// --------------------------------------------------------------------------
#include "MrMeasSrv/SeqIF/Sequence/Sequence.h"
#include "MrMeasSrv/SeqIF/Sequence/sequmsg.h"
#ifdef WIN32
#include "MrImagingFW/libMath/MrException.h"
#include "MrProtSrv/Domain/MrProtocol/UILink/MrStdNameTags.h" // NJM:
#include "MrCommon/UTrace/Macros.h"
#endif

#ifndef SEQ_NAMESPACE
#error SEQ_NAMESPACE not defined
#endif

using namespace SEQ_NAMESPACE;
#ifdef WIN32

//  ----------------------------------------------------------------------
//
//  Name        :  getSeq
//
//  Description :
/// \brief         Returns the pointer to the sequence MiniFlash
//
//  Return      :  MiniFlash*
//
//  ----------------------------------------------------------------------
MiniFlash* getSeq(MrUILinkBase* const pThis)
{
    return getSeq<MiniFlash>(pThis);
}

//  ----------------------------------------------------------------------
//
//  Name        :  getUI
//
//  Description :
/// \brief         Returns the pointer to the UI class of the MiniFlash
///                 sequence
//
//  Return      :  MiniFlashUI*
//
//  ----------------------------------------------------------------------
const MiniFlashUI* getUI(MrUILinkBase* const pThis)
{
    return getSeqUI<MiniFlashUI>(pThis);
}

bool isAvailableContentQualificationSelection(LINK_SELECTION_TYPE* const pUILink, LINK_SELECTION_TYPE::INDEX_TYPE /*lPos*/)
{
    WPT_NAMESPACE::WIPParameterTool* pTool = WPT_NAMESPACE::WIPParameterTool::getInstanceFor(*pUILink);

    // Enable ContentQualification selection only if ContentQualification checkbox is checked
    return true == pTool->getBoolValue(WPT_POS_SETCONTENTQ_ENABLED);
}

bool isAvailableContentQualificationCheckbox(LINK_BOOL_TYPE* const /*pUILink*/, LINK_BOOL_TYPE::INDEX_TYPE /*lPos*/)
{
    // always show ContentQualification checkbox
    return true;
}

// --------------------------------------------------------------------------------------------
///  \brief    This tool tip handler creates a tool tip text for the parameter WIPBool.
///
///            The text contains some information about the current measurement.
// --------------------------------------------------------------------------------------------
unsigned int toolTipHandlerContentQualificationCheckbox(LINK_BOOL_TYPE* const pUILink, char* arg_list[], LINK_BOOL_TYPE::INDEX_TYPE /*lPos*/)
{
    MrProt rMrProt(pUILink->prot());

    // prepare sequence (required to get sequence exports)
    if (!pUILink->sequence().prepareForBinarySearch(rMrProt))
    {
        THROW_MR_MSG(MrException, "Could not prepare sequence in customized ToolTipHandler!");
    }

    // build tool tip text
    std::ostringstream TmpStream;
    TmpStream << "IMPORTANT: Consult the IDEA manual before setting this option!" << std::endl;
    TmpStream << std::endl;
    TmpStream << "Enable custom setter for DICOM ContentQualification tag" << std::endl;
    TmpStream << std::endl;
    TmpStream << "Default if not set (checkbox disabled): RESEARCH" << std::endl;

    // copy text into static variable sToolTip -> will still exist after leaving this method
    // tlo20160303: solve Coverity CID 26861: copy into fixed size buffer
    static char sToolTip[2048];

    if (syngo::MR::strlcpy(sToolTip, TmpStream.str().c_str(), sizeof(sToolTip)) >= sizeof(sToolTip))
    {
        THROW_MR_MSG(MrException, "Tool tip string too long");
    }

    // fill arg_list
    arg_list[0] = sToolTip;

    // tell UI to display the text in arg_list [0];
    return MRI_STD_STRING;
}

// --------------------------------------------------------------------------------------------
///  \brief    This tool tip handler creates a tool tip text for the parameter WIPBool.
///
///            The text contains some information about the current measurement.
// --------------------------------------------------------------------------------------------
unsigned int toolTipHandlerContentQualificationSelection(LINK_SELECTION_TYPE* const pUILink, char* arg_list[], LINK_SELECTION_TYPE::INDEX_TYPE /*lPos*/)
{
    MrProt rMrProt(pUILink->prot());

    // prepare sequence (required to get sequence exports)
    if (!pUILink->sequence().prepareForBinarySearch(rMrProt))
    {
        THROW_MR_MSG(MrException, "Could not prepare sequence in customized ToolTipHandler!");
    }

    // build tool tip text
    std::ostringstream TmpStream;
    TmpStream << "IMPORTANT: Consult the IDEA manual before setting this option!" << std::endl;
    TmpStream << std::endl;
    TmpStream << "Set custom value for DICOM ContentQualification tag:" << std::endl;
    TmpStream << std::endl;
    TmpStream << "UNDEFINED:  will use system default in resulting DICOMs" << std::endl;
    TmpStream << "RESEARCH :  will set ContentQualification to RESEARCH" << std::endl;
    TmpStream << "PRODUCT  :  will set ContentQualification to PRODUCT" << std::endl;
    TmpStream << "            REMARK: in that case YOU as customer are responsible to make sure your development process complies to the specification of medical software!" << std::endl;
    TmpStream << "SERVICE  :  will set ContentQualification to SERVICE (e.g. for service sequences)" << std::endl;

    // copy text into static variable sToolTip -> will still exist after leaving this method
    // tlo20160303: solve Coverity CID 26861: copy into fixed size buffer
    static char sToolTip[2048];

    if (syngo::MR::strlcpy(sToolTip, TmpStream.str().c_str(), sizeof(sToolTip)) >= sizeof(sToolTip))
    {
        THROW_MR_MSG(MrException, "Tool tip string too long");
    }

    // fill arg_list
    arg_list[0] = sToolTip;

    // tell UI to display the text in arg_list [0];
    return MRI_STD_STRING;
}

// -------------------------------
// NJM
unsigned _WIP_Long_GetLabelId(LINK_LONG_TYPE* const, char* arg_list[], int32_t lIndex)
{
	static const char* const pszLabel0 = "Num. Shots";
	switch (lIndex)
    {
    case WIPLong_NumShots:	        arg_list[0] = (char*)pszLabel0; break;
    }
	return MRI_STD_STRING;
}

unsigned _WIP_Long_GetUnitId(LINK_LONG_TYPE* const, char* arg_list[], int32_t lIndex)
{
    static const char* const pszLabel0 = "";
    switch (lIndex)
    {
    case WIPLong_NumShots:	        arg_list[0] = (char*)pszLabel0; break;
    }
	return MRI_STD_STRING;
}

bool _WIP_Long_IsAvailable(LINK_LONG_TYPE* const pThis, int32_t lIndex)
{
    MrProt sThisProt(&pThis->prot());
	return true;
}

bool _WIP_Long_GetLimits(LINK_LONG_TYPE* const, std::vector<MrLimitLong>& rLimitVector, uint32_t& rulVerify, int32_t lIndex)
{
    //rulVerify = LINK_LONG_TYPE::VERIFY_BINARY_SEARCH;
	rulVerify = LINK_LONG_TYPE::VERIFY_SCAN_ALL;
    rLimitVector.resize(1);
    switch (lIndex)
    {
    case WIPLong_NumShots:	        rLimitVector[0].setEqualSpaced(2, 8, 2); break;
    }
	return true;
}

int32_t _WIP_Long_GetValue(LINK_LONG_TYPE* const pThis, int32_t lIndex)
{
	MrProt sThisProt(&pThis->prot());  // MrProt wrapper

    switch (lIndex)
    {
    case WIPLong_NumShots:	        return sThisProt.getsWipMemBlock().getalFree()[WIPLong_NumShots]; break;
    }

    return 0;
}

int32_t _WIP_Long_SetValue(LINK_LONG_TYPE* const pThis, int32_t value, int32_t lIndex)
{
	MrProt sThisProt(&pThis->prot()); // MrProt wrapper

    switch (lIndex)
    {
    case WIPLong_NumShots:          return sThisProt.getsWipMemBlock().getalFree()[WIPLong_NumShots] = value; break;
    }
    return 0;
}

unsigned _WIP_Long_ToolTip(LINK_LONG_TYPE* const pThis, char* arg_list[], int32_t lIndex)
{
	MrProt sThisProt(&pThis->prot());  // MrProt wrapper
    
	const size_t size = 1000000;
	static char tToolTip[size];
	static char tLine[10000];
	tToolTip[0] = '\0';


	switch (lIndex) 
    {
    case WIPLong_NumShots:
    {
        sprintf(tLine, "");
        strncat(tToolTip, tLine, size);
        break;
    }

	default:
		sprintf(tLine, "");
		strncat(tToolTip, tLine, size);
		break;
	}

	arg_list[0] = tToolTip;
	return MRI_STD_STRING;

}

#endif // end of WIN32

//  --------------------------------------------------------------------------
//
//  Name        : registerUI
//
//  Description :
/// \brief        This method registers all given set / get / Solve - handlers
///
///               It can be executed on the measurement system, too, but is empty there.
///
///
///               It returns an NLS status
///
//  Return      : long
//
//  --------------------------------------------------------------------------

NLS_STATUS MiniFlashUI::registerUI(SeqLim& rSeqLim, WPT_NAMESPACE::WIPParameterTool& rTool)
{
    // ----------------------------------------------------------------------------------
    // Starting with NXVA11B the ContentQualification DICOM tag will be set to RESEARCH for IDEA compiled sequences.
    // The sequence can change that default.
    //
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // IMPORTANT: Consult the IDEA manual before setting this option.
    // If you set the value to PRODUCT, you have to make sure (and document) that your development process complies to the specifications of medical software!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //
    // In the following example you can change the value as follows:
    // By enabling the ContentQualification checkbox and selecting a value from the selection
    //  the example sequence will enforce the selected value to be written in the ContentQualification
    //  DICOM tag of the resulting DICOM data.
    // As already stated, if nothing has been specified for ContentQualification
    //  the default value for ContentQualification for a IDEA compiled customer sequences will be "RESEARCH" (starting with NXVA11B)
    rTool.createBoolParameter(WPT_POS_SETCONTENTQ_ENABLED, rSeqLim, "Set ContentQualification", false);
    rTool.createSelectionParameter(WPT_POS_SETCONTENTQ_VALUE, rSeqLim, "ContentQualification: ", "");
    rTool.addDefaultOption(WPT_POS_SETCONTENTQ_VALUE, "UNDEFINED", (int32_t)SEQ::ContentQualification::UNDEFINED);
    rTool.addOption(WPT_POS_SETCONTENTQ_VALUE, "RESEARCH", (int32_t)SEQ::ContentQualification::RESEARCH);
    rTool.addOption(WPT_POS_SETCONTENTQ_VALUE, "PRODUCT", (int32_t)SEQ::ContentQualification::PRODUCT);
    rTool.addOption(WPT_POS_SETCONTENTQ_VALUE, "SERVICE", (int32_t)SEQ::ContentQualification::SERVICE);
    // ----------------------------------------------------------------------------------

#ifdef WIN32

    // ----------------------------------------------------------------------------------
    // Registration of available handler methods
    //
    //                                           parameter tag     new handler function
    // ----------------------------------------------------------------------------------
    // register customized tool tip handlers
    rTool.registerToolTipHandler(WPT_POS_SETCONTENTQ_ENABLED, toolTipHandlerContentQualificationCheckbox);
    rTool.registerToolTipHandler(WPT_POS_SETCONTENTQ_VALUE, toolTipHandlerContentQualificationSelection);

    // register visible handlers
    rTool.registerIsAvailableHandler(WPT_POS_SETCONTENTQ_ENABLED, isAvailableContentQualificationCheckbox);
    rTool.registerIsAvailableHandler(WPT_POS_SETCONTENTQ_VALUE, isAvailableContentQualificationSelection);

    // NJM
    if (LINK_LONG_TYPE* pLong = _create< LINK_LONG_TYPE >(rSeqLim, MR_TAG_SEQ_WIP1, WIPLong_NumShots))
    {
        pLong->registerGetLabelIdHandler(_WIP_Long_GetLabelId);
        //pLong->registerGetUnitIdHandler(_WIP_Long_GetUnitId);
        pLong->registerGetLimitsHandler(_WIP_Long_GetLimits);
        pLong->registerGetValueHandler(_WIP_Long_GetValue);
        pLong->registerSetValueHandler(_WIP_Long_SetValue);
        pLong->registerIsAvailableHandler(_WIP_Long_IsAvailable);
        //pLong->registerSolveHandler(_solveLongParamConflict);
        pLong->registerGetToolTipIdHandler(_WIP_Long_ToolTip);
    }

#endif

    return MRI_SEQ_SEQU_NORMAL;

}; // end of registerUI
