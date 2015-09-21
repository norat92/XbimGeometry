// Created on: 1991-02-26
// Created by: Isabelle GRIGNON
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

#ifndef _Extrema_LocEPCOfLocateExtPC2d_HeaderFile
#define _Extrema_LocEPCOfLocateExtPC2d_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Handle.hxx>

#include <Standard_Boolean.hxx>
#include <Standard_Real.hxx>
#include <Extrema_PCLocFOfLocEPCOfLocateExtPC2d.hxx>
class Standard_DomainError;
class Standard_TypeMismatch;
class StdFail_NotDone;
class Adaptor2d_Curve2d;
class Extrema_Curve2dTool;
class Extrema_POnCurv2d;
class gp_Pnt2d;
class gp_Vec2d;
class Extrema_PCLocFOfLocEPCOfLocateExtPC2d;
class Extrema_SeqPCOfPCLocFOfLocEPCOfLocateExtPC2d;



class Extrema_LocEPCOfLocateExtPC2d 
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT Extrema_LocEPCOfLocateExtPC2d();
  
  Standard_EXPORT Extrema_LocEPCOfLocateExtPC2d(const gp_Pnt2d& P, const Adaptor2d_Curve2d& C, const Standard_Real U0, const Standard_Real TolU);
  
  Standard_EXPORT Extrema_LocEPCOfLocateExtPC2d(const gp_Pnt2d& P, const Adaptor2d_Curve2d& C, const Standard_Real U0, const Standard_Real Umin, const Standard_Real Usup, const Standard_Real TolU);
  
  Standard_EXPORT void Initialize (const Adaptor2d_Curve2d& C, const Standard_Real Umin, const Standard_Real Usup, const Standard_Real TolU);
  
  Standard_EXPORT void Perform (const gp_Pnt2d& P, const Standard_Real U0);
  
  Standard_EXPORT Standard_Boolean IsDone() const;
  
  Standard_EXPORT Standard_Real SquareDistance() const;
  
  Standard_EXPORT Standard_Boolean IsMin() const;
  
  Standard_EXPORT const Extrema_POnCurv2d& Point() const;




protected:





private:



  Standard_Boolean myDone;
  Standard_Real mytolU;
  Standard_Real myumin;
  Standard_Real myusup;
  Extrema_PCLocFOfLocEPCOfLocateExtPC2d myF;


};







#endif // _Extrema_LocEPCOfLocateExtPC2d_HeaderFile
