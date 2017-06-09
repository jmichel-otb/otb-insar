#include "itkDefaultConvertPixelTraits.h"
#include <complex>

// This file is absolutely ugly but necessary for the whole
// ResampleImageFilter based class to not complain about std::complex
// pixel type ...

template <typename T> bool operator<(std::complex<T> const & a, std::complex<T> const & b)
{
  return abs(a)<abs(b);
}

template <typename T> bool operator>(std::complex<T> const & a, std::complex<T> const & b)
{
  return abs(a)>abs(b);
}

namespace itk
{
#define ITK_DEFAULTCONVERTTRAITS_NATIVE_SPECIAL_COMPLEX(type)                                    \
  template< >                                                                                    \
  class DefaultConvertPixelTraits< std::complex<type> >                                          \
  {                                                                                              \
  public:                                                                                        \
    typedef type ComponentType;                                                                  \
    static unsigned int GetNumberOfComponents()                                                  \
      {                                                                                          \
      return 2;                                                                                  \
      }                                                                                          \
    static unsigned int GetNumberOfComponents(const std::complex<type>)                          \
      {                                                                                          \
      return 2;                                                                                  \
      }                                                                                          \
    static void SetNthComponent(int comp, std::complex<type> & pixel, const ComponentType &v)    \
      {                                                                                          \
        if(comp == 0)                                                                            \
          pixel = std::complex<type>(v,std::imag(pixel));                                        \
        else if(comp == 1)                                                                       \
          pixel = std::complex<type>(std::real(pixel),v);                                        \
      }                                                                                          \
static void SetNthComponent(int, std::complex<type> & pixel, const std::complex<type> &v)        \
      {                                                                                          \
        pixel = v;                                                                               \
      }                                                                                          \
                                                                                                 \
    static type GetNthComponent(int comp, const std::complex<type> pixel)                        \
      {                                                                                          \
        if(comp == 0)                                                                            \
          return pixel.real();                                                                   \
        if(comp == 0)                                                                            \
          return pixel.imag();                                                                   \
      }                                                                                          \
    static type GetScalarValue(const std::complex<type> &pixel)                                  \
      {                                                                                          \
      return pixel.real();                                                                       \
      }                                                                                          \
  };

ITK_DEFAULTCONVERTTRAITS_NATIVE_SPECIAL_COMPLEX(float)
ITK_DEFAULTCONVERTTRAITS_NATIVE_SPECIAL_COMPLEX(double)


#undef ITK_DEFAULTCONVERTTRAITS_NATIVE_SPECIAL_COMPLEX

}; // End namespace ITK
