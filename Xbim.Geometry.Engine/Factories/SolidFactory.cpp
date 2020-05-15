#include "SolidFactory.h"
#include <gp_Ax2.hxx>
#include "../BRep/XbimSolid.h"
using namespace Xbim::Geometry::BRep;
namespace Xbim
{
	namespace Geometry
	{
		namespace Factories
		{
            IXSolid^ SolidFactory::Build(IIfcSolidModel^ ifcSolid)
            {
                TopoDS_Solid topoSolid = BuildSolidModel(ifcSolid);
                if (topoSolid.IsNull()) throw gcnew XbimGeometryFactoryException("Failure building IfcSolidModel");
                return gcnew XbimSolid(topoSolid);
            }

            IXSolid^ SolidFactory::Build(IIfcCsgPrimitive3D^ ifcCsgPrimitive)
            {
                TopoDS_Solid topoSolid = BuildCsgPrimitive3D(ifcCsgPrimitive);
                if (topoSolid.IsNull()) 
                    throw gcnew XbimGeometryFactoryException("Failure building IfcCsgPrimitive3D");
                return gcnew XbimSolid(topoSolid);
            }

            ///this method builds all solid models and is the main entry point
            //all methods called will throw an excpetion if they cannot build their part of a solid
            TopoDS_Solid SolidFactory::BuildSolidModel(IIfcSolidModel^ ifcSolid)
            {
                XSolidModelType solidModelType;
                if (!Enum::TryParse<XSolidModelType>(ifcSolid->ExpressType->ExpressName, solidModelType))
                    throw gcnew XbimGeometryFactoryException("Unsupported solidmodel type: " + ifcSolid->ExpressType->ExpressName);
                switch (solidModelType)
                {
               
                case XSolidModelType::IfcSweptDiskSolid:
                    break;
                case XSolidModelType::IfcSweptDiskSolidPolygonal:
                    break;
                case XSolidModelType::IfcAdvancedBrep:
                    break;
                case XSolidModelType::IfcAdvancedBrepWithVoids:
                    break;
                case XSolidModelType::IfcFacetedBrep:
                    break;
                case XSolidModelType::IfcFacetedBrepWithVoids:
                    break;
                case XSolidModelType::IfcExtrudedAreaSolid:
                    break;
                case XSolidModelType::IfcExtrudedAreaSolidTapered:
                    break;
                case XSolidModelType::IfcFixedReferenceSweptAreaSolid:
                    break;
                case XSolidModelType::IfcRevolvedAreaSolid:
                    break;
                case XSolidModelType::IfcRevolvedAreaSolidTapered:
                    break;
                case XSolidModelType::IfcSurfaceCurveSweptAreaSolid:
                    break;
                default:
                    break;
                }
                throw gcnew XbimGeometryFactoryException("Not implemented. SolidModel type: " + solidModelType.ToString());
            }

            TopoDS_Solid SolidFactory::BuildCsgSolid(IIfcCsgSolid^ ifcCsgSolid)
            {
                //at the root of a csg solid is either a boolean result or a csg solid primitive
                IIfcBooleanResult^ booleanResult = dynamic_cast<IIfcBooleanResult^>(ifcCsgSolid->TreeRootExpression);
                if (booleanResult != nullptr) return BuildBooleanResult(booleanResult);
                IIfcCsgPrimitive3D^ primitive3d = dynamic_cast<IIfcCsgPrimitive3D^>(ifcCsgSolid->TreeRootExpression);
                if (primitive3d == nullptr) throw gcnew XbimGeometryFactoryException("Unsupported TreeRootExpression type");
                return BuildCsgPrimitive3D(primitive3d);
            }

            TopoDS_Solid SolidFactory::BuildBooleanResult(IIfcBooleanResult^ ifcBooleanResult)
            {
                throw gcnew System::NotImplementedException();
                // TODO: insert return statement here
            }

            TopoDS_Solid SolidFactory::BuildCsgPrimitive3D(IIfcCsgPrimitive3D^ ifcCsgPrimitive3D)
            {

                XCsgPrimitive3dType csgType;
                if (!Enum::TryParse<XCsgPrimitive3dType>(ifcCsgPrimitive3D->ExpressType->ExpressName, csgType))
                    throw gcnew XbimGeometryFactoryException("Unsupported CsgPrimitive3D type: " + ifcCsgPrimitive3D->ExpressType->ExpressName);
                switch (csgType)
                {
                case XCsgPrimitive3dType::IfcBlock:
                    return BuildBlock(static_cast<IIfcBlock^>(ifcCsgPrimitive3D));
                case XCsgPrimitive3dType::IfcRectangularPyramid:
                    return BuildRectangularPyramid(static_cast<IIfcRectangularPyramid^>(ifcCsgPrimitive3D));
                case XCsgPrimitive3dType::IfcRightCircularCone:
                    return BuildRightCircularCone(static_cast<IIfcRightCircularCone^>(ifcCsgPrimitive3D));
                case XCsgPrimitive3dType::IfcRightCircularCylinder:
                    return BuildRightCircularCylinder(static_cast<IIfcRightCircularCylinder^>(ifcCsgPrimitive3D));
                case XCsgPrimitive3dType::IfcSphere:
                    return BuildSphere(static_cast<IIfcSphere^>(ifcCsgPrimitive3D));
                default:
                    break;
                }
                throw gcnew XbimGeometryFactoryException("Not implemented. CsgPrimitive3D type: " + csgType.ToString());
            }

            TopoDS_Solid SolidFactory::BuildBlock(IIfcBlock^ ifcBlock)
            {
                gp_Ax2 ax2 = _gpFactory->BuildAxis2Placement(ifcBlock->Position); //must be 3D according to schema
                if (ifcBlock->XLength <= 0 || ifcBlock->YLength <= 0 || ifcBlock->ZLength <= 0)
                    throw gcnew XbimGeometryFactoryException("Csg block is a solid with zero volume");
                return Ptr()->BuildBlock(ax2, ifcBlock->XLength, ifcBlock->YLength, ifcBlock->ZLength);
                
            }

            TopoDS_Solid SolidFactory::BuildRectangularPyramid(IIfcRectangularPyramid^ ifcRectangularPyramid)
            {
                gp_Ax2 ax2 = _gpFactory->BuildAxis2Placement(ifcRectangularPyramid->Position); //must be 3D according to schema
                if (ifcRectangularPyramid->XLength <= 0 || ifcRectangularPyramid->YLength <= 0 || ifcRectangularPyramid->Height <= 0)
                    throw gcnew XbimGeometryFactoryException("Csg Rectangular Pyramid is a solid with zero volume");
                return Ptr()->BuildRectangularPyramid(ax2, ifcRectangularPyramid->XLength, ifcRectangularPyramid->YLength, ifcRectangularPyramid->Height);
            }

            TopoDS_Solid SolidFactory::BuildRightCircularCone(IIfcRightCircularCone^ ifcRightCircularCone)
            {
                gp_Ax2 ax2 = _gpFactory->BuildAxis2Placement(ifcRightCircularCone->Position); //must be 3D according to schema
                if (ifcRightCircularCone->BottomRadius <= 0 || ifcRightCircularCone->Height <= 0 )
                    throw gcnew XbimGeometryFactoryException("Csg RightCircularCone is a solid with zero volume");
                return Ptr()->BuildRightCircularCone(ax2, ifcRightCircularCone->BottomRadius, ifcRightCircularCone->Height);
            }

            TopoDS_Solid SolidFactory::BuildRightCircularCylinder(IIfcRightCircularCylinder ^ (ifcRightCircularCylinder))
            {
                gp_Ax2 ax2 = _gpFactory->BuildAxis2Placement(ifcRightCircularCylinder->Position); //must be 3D according to schema
                if (ifcRightCircularCylinder->Radius <= 0 || ifcRightCircularCylinder->Height <= 0)
                    throw gcnew XbimGeometryFactoryException("Csg RightCircularCylinder is a solid with zero volume");
                return Ptr()->BuildRightCylinder(ax2, ifcRightCircularCylinder->Radius, ifcRightCircularCylinder->Height);
            }

            TopoDS_Solid SolidFactory::BuildSphere(IIfcSphere^ ifcSphere)
            {
                gp_Ax2 ax2 = _gpFactory->BuildAxis2Placement(ifcSphere->Position); //must be 3D according to schema
                if (ifcSphere->Radius <= 0 )
                    throw gcnew XbimGeometryFactoryException("Csg Sphere is a solid with zero volume");
                return Ptr()->BuildSphere(ax2, ifcSphere->Radius);
            }

		}
	}
}