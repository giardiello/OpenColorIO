// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the OpenColorIO Project.

#include "fileformats/amf/AMFParser.cpp"

#include "testutils/UnitTest.h"
#include "UnitTestUtils.h"

namespace OCIO_NAMESPACE
{
	OCIO_ADD_TEST(AMFParser, CreateFromAMF_slogtopq)
	{
		AMFInfoRcPtr amfInfoObject = std::make_shared<AMFInfo>();
		std::string amfFilePath(GetTestFilesDir() + "/amf/slogtopq.amf");
		ConstConfigRcPtr amfConfig = CreateFromAMF(amfInfoObject, amfFilePath.c_str());

        int numRoles = amfConfig->getNumRoles();
        OCIO_REQUIRE_ASSERT(numRoles > 0);

        for (int i = 0; i < numRoles; i++)
        {
            std::string roleName = amfConfig->getRoleName(i);
            if (roleName.find("amf_clip_") == 0)
            {
                std::string srcColorSpace = amfConfig->getRoleColorSpace(i);
                std::string activeDisplays = amfConfig->getActiveDisplays();
                std::vector<std::string> listActiveDisplays;
                std::stringstream ss(activeDisplays);
                std::string token;
                while (std::getline(ss, token, ','))
                {
                    listActiveDisplays.push_back(token);
                }
                OCIO_REQUIRE_ASSERT(listActiveDisplays.size() == 1);

                std::string activeDisplay = listActiveDisplays.at(0);
                std::string activeViews = amfConfig->getActiveViews();
                std::vector<std::string> listActiveViews;
                ss.clear();
                ss.str(activeViews);
                while (std::getline(ss, token, ','))
                {
                    listActiveViews.push_back(token);
                }
                OCIO_REQUIRE_ASSERT(listActiveViews.size() == 1);

                std::string activeView = listActiveViews.at(0);
                OCIO_REQUIRE_ASSERT(activeDisplay.compare(srcColorSpace) != 0);

                DisplayViewTransformRcPtr transform = DisplayViewTransform::Create();
                transform->setSrc(srcColorSpace.c_str());
                transform->setDisplay(activeDisplay.c_str());
                transform->setView(activeView.c_str());
                transform->validate();

                ConstProcessorRcPtr processor = amfConfig->getProcessor(transform);
                OCIO_CHECK_ASSERT(processor);

                return;
            }

        }
        OCIO_REQUIRE_ASSERT(true);
	}

    OCIO_ADD_TEST(AMFParser, CreateFromAMF_slogtopq_wlook)
    {
        AMFInfoRcPtr amfInfoObject = std::make_shared<AMFInfo>();
        std::string amfFilePath(GetTestFilesDir() + "/amf/slogtopq_wlook.amf");
        ConstConfigRcPtr amfConfig = CreateFromAMF(amfInfoObject, amfFilePath.c_str());

        int numRoles = amfConfig->getNumRoles();
        OCIO_REQUIRE_ASSERT(numRoles > 0);

        for (int i = 0; i < numRoles; i++)
        {
            std::string roleName = amfConfig->getRoleName(i);
            if (roleName.find("amf_clip_") == 0)
            {
                std::string srcColorSpace = amfConfig->getRoleColorSpace(i);
                std::string activeDisplays = amfConfig->getActiveDisplays();
                std::vector<std::string> listActiveDisplays;
                std::stringstream ss(activeDisplays);
                std::string token;
                while (std::getline(ss, token, ','))
                {
                    listActiveDisplays.push_back(token);
                }
                OCIO_REQUIRE_ASSERT(listActiveDisplays.size() == 1);

                std::string activeDisplay = listActiveDisplays.at(0);
                std::string activeViews = amfConfig->getActiveViews();
                std::vector<std::string> listActiveViews;
                ss.clear();
                ss.str(activeViews);
                while (std::getline(ss, token, ','))
                {
                    listActiveViews.push_back(token);
                }
                OCIO_REQUIRE_ASSERT(listActiveViews.size() == 1);

                std::string activeView = listActiveViews.at(0);
                OCIO_REQUIRE_ASSERT(activeDisplay.compare(srcColorSpace) != 0);

                DisplayViewTransformRcPtr transform = DisplayViewTransform::Create();
                transform->setSrc(srcColorSpace.c_str());
                transform->setDisplay(activeDisplay.c_str());
                transform->setView(activeView.c_str());
                transform->validate();

                ConstProcessorRcPtr processor = amfConfig->getProcessor(transform);
                OCIO_CHECK_ASSERT(processor);

                return;
            }

        }
        OCIO_REQUIRE_ASSERT(true);
    }

} // namespace OCIO_NAMESPACE
