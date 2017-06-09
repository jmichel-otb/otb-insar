/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkResampleComplexImageFilter_h
#define itkResampleComplexImageFilter_h

#include "itkResampleImageFilter.h"
#include "itkDefaultConvertPixelTraitsComplex.h"

namespace itk
{
/** \class ResampleComplexImageFilter
 * \brief Specialization to resample complex images
 *
 */
template< typename TInputImage,
          typename TOutputImage,
          typename TInterpolatorPrecisionType = double,
          typename TTransformPrecisionType = TInterpolatorPrecisionType>
class ResampleComplexImageFilter :
    public itk::ResampleImageFilter<TInputImage,TOutputImage,TInterpolatorPrecisionType,TTransformPrecisionType>
{
public:
  /** Standard class typedefs. */
  typedef ResampleComplexImageFilter                      Self;
  typedef itk::ResampleImageFilter<TInputImage,TOutputImage,TInterpolatorPrecisionType,TTransformPrecisionType> Superclass;
  typedef SmartPointer< Self >                            Pointer;
  typedef SmartPointer< const Self >                      ConstPointer;

  typedef TInputImage                           InputImageType;
  typedef TOutputImage                          OutputImageType;
  typedef typename InputImageType::Pointer      InputImagePointer;
  typedef typename InputImageType::ConstPointer InputImageConstPointer;
  typedef typename OutputImageType::Pointer     OutputImagePointer;
  typedef typename InputImageType::RegionType   InputImageRegionType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ResampleComplexImageFilter, ResampleImageFilter);

  typedef typename Superclass::InterpolatorOutputType  InterpolatorOutputType;
  typedef typename Superclass::InterpolatorConvertType InterpolatorConvertType;
  typedef typename Superclass::ComponentType           ComponentType;
  typedef typename Superclass::PixelType               PixelType;

protected:
  ResampleComplexImageFilter()  {}
  ~ResampleComplexImageFilter() {}

  virtual PixelType CastPixelWithBoundsChecking( const InterpolatorOutputType value,
                                                 const ComponentType minComponent,
                                                 const ComponentType maxComponent) const
  {
    const unsigned int nComponents = InterpolatorConvertType::GetNumberOfComponents(value);
    PixelType          outputValue;

    NumericTraits<PixelType>::SetLength( outputValue, nComponents );

    for (unsigned int n=0; n<nComponents; n++)
      {
      ComponentType component = InterpolatorConvertType::GetNthComponent( n, value );
      
      if ( std::abs(component) < std::abs(minComponent) )
        {
        PixelConvertType::SetNthComponent( n, outputValue, static_cast<PixelComponentType>( minComponent ) );
        }
      else if ( std::abs(component) > std::abs(maxComponent) )
        {
        PixelConvertType::SetNthComponent( n, outputValue, static_cast<PixelComponentType>( maxComponent ) );
        }
      else
        {
        PixelConvertType::SetNthComponent(n, outputValue,
                                          static_cast<PixelComponentType>( component ) );
      }
      }

  return outputValue;
  }

private:
  ResampleComplexImageFilter(const Self &) ITK_DELETE_FUNCTION;
  void operator=(const Self &) ITK_DELETE_FUNCTION;
};
} // end namespace itk

#endif
