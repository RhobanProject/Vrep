// This file is part of the URDF PLUGIN for V-REP
//  
// Copyright 2006-2014 Coppelia Robotics GmbH. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// A big thanks to Ignacio Tartavull for his precious help!
// 
// The URDF PLUGIN is licensed under the terms of GNU GPL:
// 
// -------------------------------------------------------------------
// The URDF PLUGIN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// THE URDF PLUGIN IS DISTRIBUTED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY. THE USER WILL USE IT AT HIS/HER OWN RISK. THE ORIGINAL
// AUTHORS AND COPPELIA ROBOTICS GMBH WILL NOT BE LIABLE FOR DATA LOSS,
// DAMAGES, LOSS OF PROFITS OR ANY OTHER KIND OF LOSS WHILE USING OR
// MISUSING THIS SOFTWARE.
// 
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the URDF PLUGIN.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------

//
// This file was automatically created for V-REP release V3.1.3 on Sept. 30th 2014

// The URDF plugin is courtesy of Ignacio Tartavull. A few modifications by Marc.

#include "link.h"
	
urdfElement::urdfElement()
{
		 xyz[0]= 0;				xyz[1]= 0;				xyz[2]= 0;
		 rpy[0]= 0;				rpy[1]= 0;				rpy[2]= 0;
		 box_size[0]= 0;			box_size[1]= 0;			box_size[2]= 0;	
		 sphere_size[0]= 0;		sphere_size[1]= 0;		sphere_size[2]= 0;
		 cylinder_size[0]= 0;    cylinder_size[1]= 0;		cylinder_size[2]= 0;
		 rgba[0]=0.4f;			rgba[1]=0.4f;			rgba[2]=0.4f;	rgba[3]=0.0f;
		 mesh_scaling[0]=1.0f;
		 mesh_scaling[1]=1.0f;
		 mesh_scaling[2]=1.0f;

         n = -1;
}

urdfLink::urdfLink()
{
	//Initialize arrays
		//Variables Inertial
		 inertial_xyz[0]= 0;			inertial_xyz[1]= 0;				inertial_xyz[2]= 0;
		 inertial_rpy[0]= 0;			inertial_rpy[1]= 0;				inertial_rpy[2]= 0;

		 mass = 1.0f;
		 inertia[8] = 0.0f; inertia[7] = 0; inertia[6] = 0; inertia[5] = 0; inertia[4] = 0.0f; inertia[3] = 0; inertia[2] = 0; inertia[1] = 0; inertia[0] = 0.0f;
		inertiaPresent=false;

		nParent=-1;
		nChild=-1;
		nLinkCollision=-1;
        nLinkVisual=-1;
}

void urdfLink::addVisual()
{
    visuals.push_back(urdfElement());
}
    
urdfElement &urdfLink::currentVisual()
{
    return visuals[visuals.size()-1];
}

void urdfLink::addCollision()
{
    collisions.push_back(urdfElement());
}
    
urdfElement &urdfLink::currentCollision()
{
    return collisions[collisions.size()-1];
}

urdfLink::~urdfLink()
{
}

void urdfLink::setPosition(std::string gazebo_xyz,std::string choose)
{
	if(choose == "inertial")
		stringToArray(inertial_xyz,gazebo_xyz.c_str());
	if(choose == "visual")
		stringToArray(currentVisual().xyz,gazebo_xyz.c_str());
	if(choose == "collision")
		stringToArray(currentCollision().xyz,gazebo_xyz.c_str());
}

void urdfLink::setRotation(std::string gazebo_rpy,std::string choose)
{
	if(choose == "inertial")
		stringToArray(inertial_rpy,gazebo_rpy.c_str());
	if(choose == "visual")
		stringToArray(currentVisual().rpy,gazebo_rpy.c_str());
	if(choose == "collision")
		stringToArray(currentCollision().rpy,gazebo_rpy.c_str());
}


void urdfLink::setBox(std::string gazebo_size,std::string choose)
{
	if(choose == "visual")
	{
		stringToArray(currentVisual().box_size, gazebo_size);
	}
	if(choose == "collision")
	{
		stringToArray(currentCollision().box_size, gazebo_size);
	}
}
void urdfLink::setSphere(std::string gazebo_radius,std::string choose)
{
    urdfElement *element = NULL;

	if(choose == "visual")
	{
        element = &currentVisual();	
	}
	if(choose == "collision")
	{
        element = &currentCollision();	
	}

    if (element != NULL) {
		stringToArray(element->sphere_size,gazebo_radius+" "+gazebo_radius+" "+gazebo_radius);

		element->sphere_size[0] = element->sphere_size[0] * 2; //Radius to bounding box conversion
		element->sphere_size[1] = element->sphere_size[1] * 2; //Radius to bounding box conversion
		element->sphere_size[2] = element->sphere_size[2] * 2; //Radius to bounding box conversion
    }
}
void urdfLink::setCylinder(std::string gazebo_radius,std::string gazebo_length,std::string choose)
{
    urdfElement *element = NULL;

	if(choose == "visual")
	{
        element = &currentVisual();	
	}
	if(choose == "collision")
	{
        element = &currentCollision();	
	}

    if (element != NULL) {
        stringToArray(element->cylinder_size, gazebo_radius+" "+gazebo_radius+" "+gazebo_length);

        element->cylinder_size[0] = element->cylinder_size[0] * 2; //Radius to bounding box conversion
        element->cylinder_size[1] = element->cylinder_size[1] * 2; //Radius to bounding box conversion
    }
}

void urdfLink::setColor(std::string color)
{
	stringToArray(currentVisual().rgba,color);
}

void urdfLink::setMass(std::string gazebo_mass)
{
	mass=getFloat(gazebo_mass);
}
void urdfLink::setInertia(int position, std::string gazebo_inertia_number)
{
	inertia[position] = getFloat(gazebo_inertia_number);
}
void urdfLink::verifyInertia()
{
	float c=0.0f;
	for (int i=0;i<9;i++)
		c+=fabs(inertia[i]);
	if (c==0.0f)
	{
		std::string txt("ERROR: found an invalid inertia entry for link '"+ name+"'");
		printToConsole(txt.c_str());

		inertia[0]=0.001f;
		inertia[4]=0.001f;
		inertia[8]=0.001f;
	}
}

void urdfLink::setMeshFilename(std::string packagePath,std::string meshFilename,std::string choose)
{
    std::cout << std::flush;

	std::string meshFilename_alt; // we use an alternative filename... the package location is somewhat strangely defined sometimes!!
	if (meshFilename.compare(0,10,"package://")==0) // condition added by Marc on 17/1/2014
	{
		meshFilename = meshFilename.substr(9,meshFilename.size()); //to delete de package:/ part
		meshFilename_alt=meshFilename;
		meshFilename = packagePath + meshFilename;
		packagePath = packagePath.substr(0, packagePath.find_last_of("/"));
		meshFilename_alt = packagePath + meshFilename_alt;
	}

	std::string extension = meshFilename.substr(meshFilename.size()-3,meshFilename.size());
	int nExtension;
	if(extension == "obj" || extension =="OBJ"){ nExtension = 0;}
	else if(extension == "dxf" || extension == "DXF"){ nExtension = 1;}
	else if(extension == "3ds" || extension == "3DS"){ nExtension = 2;}
	else if(extension == "stl" || extension == "STL"){ nExtension = 4;}
	else if(extension == "dae" || extension == "DAE"){ nExtension = 5;}
	else
	{
		nExtension = -1;
		std::string txt("ERROR: the extension '"+ extension +"' is not currently a supported.");
		printToConsole(txt.c_str());
	}

	if(choose == "visual")
	{
        urdfElement &visual = currentVisual();
		visual.meshFilename = meshFilename;
		visual.meshFilename_alt = meshFilename_alt;
		visual.meshExtension = nExtension;
	}
	if(choose == "collision")
	{
        urdfElement &collision = currentCollision();
		collision.meshFilename = meshFilename;
		collision.meshFilename_alt = meshFilename_alt;
		collision.meshExtension = nExtension;
	}
}

static simInt groupShapes(std::vector<urdfElement> &elements)
{
    simInt n = -1;
    simInt *shapes = new simInt[elements.size()];
    int validShapes = 0;

    for (unsigned int i=0; i<elements.size(); i++) {
        urdfElement &element = elements[i];
        if (element.n!=-1) {
            simSetShapeColor(element.n,NULL,0,element.rgba);
			
            C7Vector frame;
			frame.X.set(element.xyz);
			frame.Q=getQuaternionFromRpy(element.rpy);
			
            C7Vector initFrame;
			simGetObjectPosition(element.n,-1,initFrame.X.data);
			C3Vector euler;
			simGetObjectOrientation(element.n,-1,euler.data);
			initFrame.Q.setEulerAngles(euler);
			
            C7Vector x(frame*initFrame);
            //C7Vector x(frame);

			simSetObjectPosition(element.n,-1,x.X.data);
			simSetObjectOrientation(element.n,-1,x.Q.getEulerAngles().data);

            shapes[validShapes++] = element.n;
        }
    }

    if (validShapes > 1) {
        n = simGroupShapes(shapes, validShapes);
    } else if (validShapes == 1) {
        n = shapes[0];
    }
    delete shapes;

    return n;
}

//Write
void urdfLink::createLink(bool hideCollisionLinks,bool convexDecomposeNonConvexCollidables,bool createVisualIfNone,bool& showConvexDecompositionDlg)
{
	std::string txt("Creating link '"+name+"'...");
	printToConsole(txt.c_str());

    //visuals.clear();

    // Visuals
    for (int i=0; i<visuals.size(); i++) {
        urdfElement &visual = visuals[i];
        
        if(!visual.meshFilename.empty())
        {
            std::string fname(visual.meshFilename);
            bool exists=true;
            bool useAlt=false;
            if (!simDoesFileExist(fname.c_str()))
            {
                fname=visual.meshFilename_alt;
                exists=simDoesFileExist(fname.c_str());
                useAlt=true;
            }

            if (!exists)
                printToConsole("ERROR: the mesh file could not be found.");
            else
                visual.n = simImportShape(visual.meshExtension,fname.c_str(),0,0.0001f,1.0);

            if (!visual.n)
            {
                if (!useAlt)
                    txt="ERROR: failed to create the mesh '"+visual.meshFilename+"' with extension type "+boost::lexical_cast<std::string>(visual.meshExtension);
                else
                    txt="ERROR: failed to create the mesh '"+visual.meshFilename+"' or '"+visual.meshFilename_alt+"' with extension type "+boost::lexical_cast<std::string>(visual.meshExtension);
                printToConsole(txt.c_str());
            }
            else
                visual.n = scaleShapeIfRequired(visual.n,visual.mesh_scaling);
        }
        else if (!isArrayEmpty(visual.sphere_size))
            visual.n = simCreatePureShape( 1,1+2+16, visual.sphere_size, mass, NULL);
        else if (!isArrayEmpty(visual.cylinder_size))
            visual.n = simCreatePureShape( 2,1+2+16, visual.cylinder_size, mass, NULL);
        else if (!isArrayEmpty(visual.box_size))
            visual.n = simCreatePureShape( 0,1+2+16, visual.box_size, mass, NULL);
    }

    //collisions.clear();
    //mass=0.1;

	//collision
    for (int i=0; i<collisions.size(); i++) {
        urdfElement &collision = collisions[i];

        if(!collision.meshFilename.empty())
        { 	
            std::string fname(collision.meshFilename);
            bool exists=true;
            bool useAlt=false;
            if (!simDoesFileExist(fname.c_str()))
            {
                fname=collision.meshFilename_alt;
                exists=simDoesFileExist(fname.c_str());
                useAlt=true;
            }

            if (!exists)
                printToConsole("ERROR: the mesh file could not be found");
            else
                collision.n = simImportShape(collision.meshExtension,fname.c_str(),0,0.0001f,1.0);

            if (collision.n == -1)
            {
                if (!useAlt)
                    txt="ERROR: failed to create the mesh '"+collision.meshFilename+"' with extension type "+boost::lexical_cast<std::string>(collision.meshExtension);
                else
                    txt="ERROR: failed to create the mesh '"+collision.meshFilename+"' or '"+collision.meshFilename_alt+"' with extension type "+boost::lexical_cast<std::string>(collision.meshExtension);
                printToConsole(txt.c_str());
            }
            else
            {
                collision.n=scaleShapeIfRequired(collision.n,collision.mesh_scaling);
                if (createVisualIfNone&&(visuals.size()==0))
                { // We create a visual from the collision shape (before it gets morphed hereafter):
                    simRemoveObjectFromSelection(sim_handle_all,-1);
                    simAddObjectToSelection(sim_handle_single,collision.n);
                    simCopyPasteSelectedObjects();
                    addVisual();
                    currentVisual().n = simGetObjectLastSelection();
                }
                int p;
                int convInts[5]={1,500,200,0,0}; // 3rd value from 100 to 500 on 5/2/2014
                float convFloats[5]={100.0f,30.0f,0.25f,0.0f,0.0f};
                if ( convexDecomposeNonConvexCollidables&&(simGetObjectIntParameter(collision.n,3017,&p)>0)&&(p==0) )
                {
                    int aux=1+4+8+16+64;
                    if (showConvexDecompositionDlg)
                        aux=1+2+8+16+64;
                    showConvexDecompositionDlg=false;
                    simConvexDecompose(collision.n,aux,convInts,convFloats); // we generate convex shapes!
                }
                simSetObjectIntParameter(collision.n,3003,!inertiaPresent); // we make it non-static if there is an inertia
                simSetObjectIntParameter(collision.n,3004,1); // we make it respondable since it is a collision object
            }

        }
        else if (!isArrayEmpty(collision.sphere_size))
            collision.n = simCreatePureShape( 1,1+2+4+8+16*(!inertiaPresent), collision.sphere_size, mass, NULL);
        else if (!isArrayEmpty(collision.cylinder_size))
            collision.n = simCreatePureShape( 2,1+2+4+8+16*(!inertiaPresent), collision.cylinder_size, mass, NULL);
        else if (!isArrayEmpty(collision.box_size))
            collision.n = simCreatePureShape( 0,1+2+4+8+16*(!inertiaPresent), collision.box_size, mass, NULL);
    }

    // Hack to draw COM in the collision layer
    /*
    addCollision();
    currentCollision().xyz[0] = inertial_xyz[0];
    currentCollision().xyz[1] = inertial_xyz[1];
    currentCollision().xyz[0] = inertial_xyz[2];
    currentCollision().rpy[0] = 1.5;
    float dummySize[3]={0.01f,0.01f,0.01f};
    currentCollision().n = simCreatePureShape( 1,1+2+16, dummySize, mass, NULL);
    */
    
    // Grouping collisions shapes
    nLinkCollision = groupShapes(collisions);

	// Inertia
	if (inertiaPresent)
	{
        C3Vector euler;

		if (nLinkCollision==-1)
		{ // we do not have a collision object. Let's create a dummy collision object, since inertias can't exist on their own in V-REP:
			float dummySize[3]={0.01f,0.01f,0.01f};
			//nLinkCollision = simCreatePureShape( 1,1+2+4, dummySize, mass, NULL); // we make it non-respondable!
            nLinkCollision = simCreatePureShape( 1,1+2+16, dummySize, mass, NULL);
		}

		C7Vector inertiaFrame;
		inertiaFrame.X.set(inertial_xyz);
		inertiaFrame.Q=getQuaternionFromRpy(inertial_rpy);
            
        //simSetObjectPosition(nLinkCollision,-1,inertiaFrame.X.data);
			
		//C7Vector collisionFrame;
		//collisionFrame.X.set(collision_xyz);
		//collisionFrame.Q=getQuaternionFromRpy(collision_rpy);
			
        C7Vector collisionFrame;
        simGetObjectPosition(nLinkCollision,-1,collisionFrame.X.data);
        simGetObjectOrientation(nLinkCollision,-1,euler.data);
		collisionFrame.Q.setEulerAngles(euler);

		//C4X4Matrix x((collisionFrame.getInverse()*inertiaFrame).getMatrix());
		C4X4Matrix x(inertiaFrame.getMatrix());
		float i[12]={x.M(0,0),x.M(0,1),x.M(0,2),x.X(0),x.M(1,0),x.M(1,1),x.M(1,2),x.X(1),x.M(2,0),x.M(2,1),x.M(2,2),x.X(2)};
		simSetShapeMassAndInertia(nLinkCollision,mass,inertia,C3Vector::zeroVector.data,i);
		//std::cout << "Mass: " << mass << std::endl;
	}
	else
	{
		if (nLinkCollision!=-1)
		{
			std::string txt("ERROR: found a collision object without inertia data for link '"+ name+"'. Is that link meant to be static?");
			printToConsole(txt.c_str());
		}
	}

	if (createVisualIfNone&&(visuals.size()==0)&&(nLinkCollision!=-1))
	{ // We create a visual from the collision shape (meshes were handled earlier):
        addVisual();
        urdfElement &visual = currentVisual();
		simRemoveObjectFromSelection(sim_handle_all,-1);
		simAddObjectToSelection(sim_handle_single,nLinkCollision);
		simCopyPasteSelectedObjects();
		visual.n=simGetObjectLastSelection();
		simSetObjectIntParameter(visual.n,3003,1); // we make it static since only visual
		simSetObjectIntParameter(visual.n,3004,0); // we make it non-respondable since only visual
	}

	// Set the respondable mask:
	if (nLinkCollision!=-1)
		simSetObjectIntParameter(nLinkCollision,3019,0xff00); // colliding with everything except with other objects in that tree hierarchy

    // Grouping shapes
    nLinkVisual = groupShapes(visuals);
	
    // Set the names, visibility, etc.:
	if (nLinkVisual!=-1)
	{
		setVrepObjectName(nLinkVisual,std::string(name+"_visual").c_str());
		const float specularDiffuse[3]={0.3f,0.3f,0.3f};
		if (nLinkCollision!=-1)
		{ // if we have a collision object, we attach the visual object to it, then forget the visual object
            C7Vector collisionFrame;
            C3Vector euler;
            simGetObjectPosition(nLinkCollision,-1,collisionFrame.X.data);
            simGetObjectOrientation(nLinkCollision,-1,euler.data);
            collisionFrame.Q.setEulerAngles(euler);
			 
            C7Vector visualFrame;
			simGetObjectPosition(nLinkVisual,-1,visualFrame.X.data);
			simGetObjectOrientation(nLinkVisual,-1,euler.data);
			visualFrame.Q.setEulerAngles(euler);

			C7Vector x(collisionFrame.getInverse()*visualFrame);

			simSetObjectPosition(nLinkVisual,-1,x.X.data);
			simSetObjectOrientation(nLinkVisual,-1,x.Q.getEulerAngles().data);
			simSetObjectParent(nLinkVisual,nLinkCollision,0);
		}
	}
	if (nLinkCollision!=-1)
	{
		setVrepObjectName(nLinkCollision,std::string(name+"_respondable").c_str());
		if (hideCollisionLinks)
			simSetObjectIntParameter(nLinkCollision,10,256); // we "hide" that object in layer 9
	}
}

int urdfLink::scaleShapeIfRequired(int shapeHandle,float scalingFactors[3])
{ // in future there will be a non-iso scaling function for objects in V-REP, but until then...
	if ( (scalingFactors[0]*scalingFactors[1]*scalingFactors[2]>0.99999f)&&(scalingFactors[0]>0.0f)&&(scalingFactors[1]>0.0f) )
		return(shapeHandle); // no scaling required!
	if (fabs(scalingFactors[0])<0.00001f)
		scalingFactors[0]=0.00001f*scalingFactors[0]/fabs(scalingFactors[0]);
	if (fabs(scalingFactors[1])<0.00001f)
		scalingFactors[1]=0.00001f*scalingFactors[1]/fabs(scalingFactors[1]);
	if (fabs(scalingFactors[2])<0.00001f)
		scalingFactors[2]=0.00001f*scalingFactors[2]/fabs(scalingFactors[2]);
	int newShapeHandle=shapeHandle;
	float* vertices;
	int verticesSize;
	int* indices;
	int indicesSize;
	if (simGetShapeMesh(shapeHandle,&vertices,&verticesSize,&indices,&indicesSize,NULL)!=-1)
	{
		// Scale the vertices:
		C7Vector tr;
		simGetObjectPosition(shapeHandle,-1,tr.X.data);
		C3Vector euler;
		simGetObjectOrientation(shapeHandle,-1,euler.data);
		tr.Q.setEulerAngles(euler);
		for (int i=0;i<verticesSize/3;i++)
		{
			C3Vector v(vertices+3*i);
			v*=tr;
			v(0)*=scalingFactors[0];
			v(1)*=scalingFactors[1];
			v(2)*=scalingFactors[2];
			vertices[3*i+0]=v(0);
			vertices[3*i+1]=v(1);
			vertices[3*i+2]=v(2);
		}
		// Flip the triangles (if needed)
		if (scalingFactors[0]*scalingFactors[1]*scalingFactors[2]<0.0f)
		{
			for (int i=0;i<indicesSize/3;i++)
			{
				int tmp=indices[3*i+0];
				indices[3*i+0]=indices[3*i+1];
				indices[3*i+1]=tmp;
			}
		}
		// Remove the old shape and create a new one with the scaled data:
		simRemoveObject(shapeHandle);
		newShapeHandle=simCreateMeshShape(2,20.0f*piValue/180.0f,vertices,verticesSize,indices,indicesSize,NULL);
		simReleaseBuffer((char*)vertices);
		simReleaseBuffer((char*)indices);
	}
	return(newShapeHandle);
}


