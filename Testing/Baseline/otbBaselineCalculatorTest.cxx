/*=========================================================================

   Copyright 2012 Patrick IMBO
   Contributed to ORFEO Toolbox under license Apache 2

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

=========================================================================*/
#include "itkMacro.h"

#include "otbHorizontalVerticalBaselineFunctor.h"
#include "otbBaselineCalculator.h"
#include "otbImage.h"
#include "otbImageFileReader.h"

int otbBaselineCalculatorTest(int argc, char * argv[])
{
  /** Check command line arguments. */
  if( argc < 3 )
    {
    std::cerr << "You must supply master and slave filename" << std::endl;
    return EXIT_FAILURE;
    }

  typedef otb::Functor::HorizontalVerticalBaselineFunctor        FunctorType;
  typedef otb::BaselineCalculator<FunctorType>                   BaselineCalculatorType;
  typedef BaselineCalculatorType::PlateformPositionToBaselineCalculatorType PlateformPositionToBaselineCalculatorType;

  /** Typedefs. */
  const unsigned int  Dimension = 2;
  typedef float                                       ScalarPixelType;
  typedef otb::Image<ScalarPixelType, Dimension >     ImageType;
  typedef otb::ImageFileReader<ImageType >            ReaderType;

  std::string masterFileName = argv[ 1 ];
  std::string slaveFileName = argv[ 2 ];

  ReaderType::Pointer masterImage = ReaderType::New();
  ReaderType::Pointer slaveImage = ReaderType::New();

  masterImage->SetFileName(masterFileName);
  slaveImage->SetFileName(slaveFileName);

  masterImage->UpdateOutputInformation();
  slaveImage->UpdateOutputInformation();

  // Instantiating object
  BaselineCalculatorType::Pointer baselineCalculator = BaselineCalculatorType::New();

  
  BaselineCalculatorType::PlateformPositionToBaselinePointer plateformPositionToBaseline =  PlateformPositionToBaselineCalculatorType::New();
  plateformPositionToBaseline->SetMasterPlateform(masterImage->GetOutput()->GetImageKeywordlist());
  plateformPositionToBaseline->SetSlavePlateform(slaveImage->GetOutput()->GetImageKeywordlist());

  baselineCalculator->SetPlateformPositionToBaselineCalculator(plateformPositionToBaseline);
  baselineCalculator->SetRegion(masterImage->GetOutput()->GetLargestPossibleRegion());

  baselineCalculator->Compute(otb::Functor::HorizontalVerticalBaselineFunctor::Horizontal);

  std::cout << baselineCalculator << std::endl;

  baselineCalculator->FoundMinimumTangentialBaseline();
  baselineCalculator->Compute(otb::Functor::HorizontalVerticalBaselineFunctor::Horizontal);

  std::cout << baselineCalculator << std::endl;

  return EXIT_SUCCESS;
}
