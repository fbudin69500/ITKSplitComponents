#ifndef __itkTensorComponentsImageFilter_txx
#define __itkTensorComponentsImageFilter_txx

#include "itkTensorComponentsImageFilter.h"

#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"

namespace itk
{

template< class TInputImage, class TOutputImage,
  unsigned int TComponents >
TensorComponentsImageFilter< TInputImage, TOutputImage, TComponents >
::TensorComponentsImageFilter()
{
  this->SetNumberOfOutputs( TensorComponents );
  // ImageSource only does this for the first output.
  for( unsigned int i = 1; i < TensorComponents; i++ )
    {
    this->SetNthOutput( i, this->MakeOutput( i ) );
    }
}

template< class TInputImage, class TOutputImage,
  unsigned int TComponents >
void
TensorComponentsImageFilter< TInputImage, TOutputImage, TComponents >
::ThreadedGenerateData( const OutputRegionType& outputRegion, 
  int threadId )
{
  typename InputImageType::ConstPointer input = this->GetInput();

  DataObjectPointerArray outputs = this->GetOutputs();

  typedef typename itk::ImageRegionIterator< OutputImageType >
    OutputIteratorType;
  typename itk::ImageRegionConstIterator< InputImageType > 
    inIt( input, outputRegion );
  typename std::vector< OutputIteratorType > outIts;
  unsigned int i;
  for( i = 0; i < TensorComponents; i++ )
    {
    OutputIteratorType outIt( dynamic_cast< OutputImageType* >
      ( outputs[i].GetPointer() ), outputRegion );
    outIt.GoToBegin();
    outIts.push_back( outIt );
    }
  TensorType tensor;
  for( inIt.GoToBegin(); ! inIt.IsAtEnd(); ++inIt )
    {
    tensor = inIt.Get();
    for( i = 0; i < TensorComponents; i++ )
      {
      outIts[i].Set( static_cast< PixelType >( tensor[i] ) );
      ++(outIts[i]);
      }
    }
}

} // end namespace itk

#endif
