/**
 * @file utilities.h
 * @brief
 * @copyright
 *    (c) 2017 Lutron Electronics Co., Inc.
 *    All rights reserved.
 *    The copyright notice above does not evidence any actual or intended
 *    publication of such source code. This file and the information contained
 *    herein are confidential and proprietary to Lutron Electronics Co., Inc.
 *    Unauthorized possession or use of this file or the information contained
 *    herein is prohibited. No reproduction may be made of this file without
 *    the express written permission of Lutron Electronics Co., Inc.
 * @addtogroup
 * @{
 */
#ifndef CPPSKELETON_UTILITIES_H
#define CPPSKELETON_UTILITIES_H

/*
 * ========================================================================
 * Includes
 * ========================================================================
 */

namespace util
{
template <typename T>
void streamContainerElements(std::ostream & outputStream, T const & container)
{
   auto sep("");
   for (auto const & element : container)
   {
      outputStream << sep << element;
      sep = ", ";
   }

   outputStream << "\n";
}

template <typename T>
void streamContainerContainerElements(std::ostream & outputStream, T const & container)
{
   for (auto const & element : container)
   {
      util::streamContainerElements(outputStream, element);
   }
}

}   // util

/*
 * ========================================================================
 * Class Definitions
 * ========================================================================
 */

#endif   // CPPSKELETON_UTILITIES_H

/**
 * @}
 */
