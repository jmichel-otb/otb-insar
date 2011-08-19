/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __otbComplexInterpolateImageFunction_txx
#define __otbComplexInterpolateImageFunction_txx
#include "otbComplexInterpolateImageFunction.h"

#include "otbMath.h"

namespace otb
{

/** Constructor */
template<class TInputImage, class TFunction, class TBoundaryCondition, class TCoordRep>
ComplexInterpolateImageFunction<TInputImage, TFunction, TBoundaryCondition, TCoordRep>
::ComplexInterpolateImageFunction()
{
  this->SetRadius(1);
  m_NormalizeWeight =  false;
  m_IsSumNormalizeWeight = true;
  m_NormalizeZeroFrequency.SetSize(ImageDimension);
  m_NormalizeZeroFrequency.Fill(0.0);
}

/** Destructor */
template<class TInputImage, class TFunction, class TBoundaryCondition, class TCoordRep>
ComplexInterpolateImageFunction<TInputImage, TFunction, TBoundaryCondition, TCoordRep>
::~ComplexInterpolateImageFunction()
{
}


template<class TInputImage, class TFunction, class TBoundaryCondition, class TCoordRep>
void
ComplexInterpolateImageFunction<TInputImage, TFunction, TBoundaryCondition, TCoordRep>
::SetRadius(unsigned int rad)
{
  this->GetFunction().SetRadius(rad);
  this->Modified();
}



/** Evaluate at image index position */
template<class TInputImage, class TFunction, class TBoundaryCondition, class TCoordRep>
typename ComplexInterpolateImageFunction<TInputImage, TFunction, TBoundaryCondition, TCoordRep>::OutputType
ComplexInterpolateImageFunction<TInputImage, TFunction, TBoundaryCondition, TCoordRep>
::EvaluateAtContinuousIndex(const ContinuousIndexType& index) const
{
  IndexType baseIndex;

  for (unsigned int dim = 0; dim < ImageDimension; ++dim)
	{
	baseIndex[dim] = std::floor(index[dim]);
	}

  // Position the neighborhood at the index of interest
  SizeType radius;
  radius.Fill(this->GetRadius());
  IteratorType nit = IteratorType(radius, this->GetInputImage(), this->GetInputImage()->GetBufferedRegion());
  nit.SetLocation(baseIndex);

  RealType sumFunction = 0.;
  RealType squareFunction = 0.;
  RealType resultValue = 0.;

  /** For each element of the Interpolator Kernel do :
		1. Evaluate Kernel value                    
		2. Evaluate the bandshifted phase term: the frequency offset from baseband. 
		3. Read Pixel value
		4. Apply the bandshifted phase term to the PixelValue
	*/
  for(unsigned int elt = 0 ; elt < nit.Size(); ++elt) 
	{
		IteratorType::OffsetType offset = nit.GetOffset(elt);
		IteratorType::IndexType  currentIndex = nit.GetIndex();
		RealType  valueFunction = 1.0;
		RealType phase(1.0,0.0);
		for(unsigned int dim = 0; dim < ImageDimension; ++dim)
			{
				ScalarRealType zeroFrequency = static_cast<ScalarRealType>(m_NormalizeZeroFrequency[dim]);
				ScalarRealType delta = - otb::CONST_2PI * zeroFrequency * currentIndex[dim];
				RealType localPhase(cos(delta),sin(delta));
				phase *= localPhase;
				RealType valueTmp = m_Function(offset[dim]); 
				valueFunction *=  valueTmp;
			}

		sumFunction +=  valueFunction;
		squareFunction += (valueFunction * valueFunction);

		RealType pixelValue = static_cast<RealType>(nit.GetPixel(elt));
		resultValue += valueFunction * pixelValue * phase; 
  }

  if( this->GetNormalizeWeight() )
	{
		if(this->GetIsSumNormalizeWeight())
			{
				resultValue /= sumFunction;
			}
		else
			{
				resultValue /= squareFunction;
			}
	}


  /** Apply the bandshifted back to its original center frequency after interpolation */
  for(unsigned int dim = 0; dim < ImageDimension; ++dim)
	{
		ScalarRealType zeroFrequency = static_cast<ScalarRealType>(m_NormalizeZeroFrequency[dim]);
		ScalarRealType delta = otb::CONST_2PI * zeroFrequency * baseIndex[dim];
		RealType phase(cos(delta),sin(delta));
		resultValue *= phase;
	}

  return resultValue;
}


template<class TInputImage, class TFunction, class TBoundaryCondition, class TCoordRep>
void
ComplexInterpolateImageFunction<TInputImage, TFunction, TBoundaryCondition, TCoordRep>
::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

} //namespace otb

#endif