// Created on: 1991-12-02
// Created by: Laurent PAINNOT
// Copyright (c) 1991-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _AppDef_TheFunction_HeaderFile
#define _AppDef_TheFunction_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Handle.hxx>

#include <Standard_Boolean.hxx>
#include <AppDef_MultiLine.hxx>
#include <AppParCurves_MultiCurve.hxx>
#include <Standard_Integer.hxx>
#include <math_Vector.hxx>
#include <Standard_Real.hxx>
#include <math_Matrix.hxx>
#include <AppDef_TheLeastSquares.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <AppParCurves_HArray1OfConstraintCouple.hxx>
#include <math_MultipleVarFunctionWithGradient.hxx>
#include <AppParCurves_Constraint.hxx>
class AppDef_MultiLine;
class AppDef_MyLineTool;
class AppDef_TheLeastSquares;
class AppDef_TheResol;
class AppParCurves_MultiCurve;



class AppDef_TheFunction  : public math_MultipleVarFunctionWithGradient
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT AppDef_TheFunction(const AppDef_MultiLine& SSP, const Standard_Integer FirstPoint, const Standard_Integer LastPoint, const Handle(AppParCurves_HArray1OfConstraintCouple)& TheConstraints, const math_Vector& Parameters, const Standard_Integer Deg);
  
  Standard_EXPORT Standard_Integer NbVariables() const;
  
  Standard_EXPORT Standard_Boolean Value (const math_Vector& X, Standard_Real& F);
  
  Standard_EXPORT Standard_Boolean Gradient (const math_Vector& X, math_Vector& G);
  
  Standard_EXPORT Standard_Boolean Values (const math_Vector& X, Standard_Real& F, math_Vector& G);
  
  Standard_EXPORT const math_Vector& NewParameters() const;
  
  Standard_EXPORT const AppParCurves_MultiCurve& CurveValue();
  
  Standard_EXPORT Standard_Real Error (const Standard_Integer IPoint, const Standard_Integer CurveIndex) const;
  
  Standard_EXPORT Standard_Real MaxError3d() const;
  
  Standard_EXPORT Standard_Real MaxError2d() const;
  
  Standard_EXPORT AppParCurves_Constraint FirstConstraint (const Handle(AppParCurves_HArray1OfConstraintCouple)& TheConstraints, const Standard_Integer FirstPoint) const;
  
  Standard_EXPORT AppParCurves_Constraint LastConstraint (const Handle(AppParCurves_HArray1OfConstraintCouple)& TheConstraints, const Standard_Integer LastPoint) const;




protected:

  
  Standard_EXPORT void Perform (const math_Vector& X);




private:



  Standard_Boolean Done;
  AppDef_MultiLine MyMultiLine;
  AppParCurves_MultiCurve MyMultiCurve;
  Standard_Integer Degre;
  math_Vector myParameters;
  Standard_Real FVal;
  math_Vector ValGrad_F;
  math_Matrix MyF;
  math_Matrix PTLX;
  math_Matrix PTLY;
  math_Matrix PTLZ;
  math_Matrix A;
  math_Matrix DA;
  AppDef_TheLeastSquares MyLeastSquare;
  Standard_Boolean Contraintes;
  Standard_Integer NbP;
  Standard_Integer NbCu;
  Standard_Integer Adeb;
  Standard_Integer Afin;
  Handle(TColStd_HArray1OfInteger) tabdim;
  Standard_Real ERR3d;
  Standard_Real ERR2d;
  Standard_Integer FirstP;
  Standard_Integer LastP;
  Handle(AppParCurves_HArray1OfConstraintCouple) myConstraints;


};







#endif // _AppDef_TheFunction_HeaderFile
