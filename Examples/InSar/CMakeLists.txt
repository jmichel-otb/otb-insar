
ADD_EXECUTABLE(BasicInterferogramComputation BasicInterferogramComputation.cxx)
TARGET_LINK_LIBRARIES(BasicInterferogramComputation OTBCommon OTBImageIO)

ADD_EXECUTABLE(BaselineComputation BaselineComputation.cxx)
TARGET_LINK_LIBRARIES(BaselineComputation OTBCommon OTBImageIO Baseline)

IF(VTK_FOUND)
ADD_EXECUTABLE(BaselinePlot BaselinePlot.cxx)
TARGET_LINK_LIBRARIES(BaselinePlot OTBCommon OTBImageIO Baseline vtkHybrid vtkCharts)
ENDIF(VTK_FOUND)

ADD_EXECUTABLE(JustTheInterferogramComputation JustTheInterferogramComputation.cxx)
TARGET_LINK_LIBRARIES(JustTheInterferogramComputation OTBCommon OTBImageIO InterferogramFormation)

ADD_EXECUTABLE(JustFlatEarthRemovalInterferogramComputation JustFlatEarthRemovalInterferogramComputation.cxx)
TARGET_LINK_LIBRARIES(JustFlatEarthRemovalInterferogramComputation OTBCommon OTBImageIO InterferogramFormation)

#ADD_EXECUTABLE(SARCoregistrationComputation SARCoregistrationComputation.cxx)
#TARGET_LINK_LIBRARIES(SARCoregistrationComputation OTBCommon OTBImageIO)

ADD_EXECUTABLE(SensorModelRegistration SensorModelRegistration.cxx)
TARGET_LINK_LIBRARIES(SensorModelRegistration OTBCommon OTBImageIO Interpolation OTBTransform)

ADD_EXECUTABLE(ComplexCoarseRegistrationComputation ComplexCoarseRegistrationComputation.cxx)
TARGET_LINK_LIBRARIES(ComplexCoarseRegistrationComputation OTBCommon OTBImageIO Interpolation OTBTransform)

ADD_EXECUTABLE(FFTConvolutionTest FFTConvolutionTest.cxx)
TARGET_LINK_LIBRARIES(FFTConvolutionTest OTBCommon OTBImageIO Interpolation)

ADD_EXECUTABLE(CoherenceComputation CoherenceComputation.cxx)
TARGET_LINK_LIBRARIES(CoherenceComputation OTBCommon OTBImageIO)

#ADD_EXECUTABLE(ComplexCoarseFineStepTest ComplexCoarseFineStepTest.cxx)
#TARGET_LINK_LIBRARIES(ComplexCoarseFineStepTest OTBCommon OTBImageIO Interpolation)

# Note: couldn't compile this, had to deactivate (emmanuel)
#ADD_EXECUTABLE(InterferometricChain InterferometricChain.cxx)
#TARGET_LINK_LIBRARIES(InterferometricChain OTBCommon OTBImageIO Coregistration Interpolation InterferogramFormation)

ADD_EXECUTABLE(FlatEarthRemovalFFT FlatEarthRemovalFFT.cxx)
TARGET_LINK_LIBRARIES(FlatEarthRemovalFFT OTBCommon OTBImageIO InterferogramFormation)

ADD_EXECUTABLE(InterferogramHSVColorGeneration InterferogramHSVColorGeneration.cxx)
TARGET_LINK_LIBRARIES(InterferogramHSVColorGeneration OTBCommon OTBImageIO)

