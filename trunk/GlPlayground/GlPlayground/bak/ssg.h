#ifndef SSG_H_INCLUDED
#define SSG_H_INCLUDED

#include <list>
#include <cassert>
#include <string>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;

extern const glm::vec3 AxisX;
extern const glm::vec3 AxisY;
extern const glm::vec3 AxisZ;

/// <summary>
/// interface for any transformation between coordinate spaces
/// </summary>
class ITransformation
{
public:
    /// Transform a point
    /// </summary>
    /// <param name="point">Point in parent space to be transformed to child space</param>
    /// <returns>Transformed location</returns>
    virtual glm::vec3 Transform(const glm::vec3& point) const = 0;

    /// <summary>
    /// Transform a point with the inverse Transformation
    /// </summary>
    /// <param name="point">Point in child space to be transformed to parent space</param>
    /// <returns>Transformed location</returns>
    virtual glm::vec3 TransformInverse(glm::vec3 point) const = 0;

    /// <summary>
    /// Return the inverse of the present transformation
    /// </summary>
    //virtual ITransformation GetInverse() const = 0;

    /// <summary>
    /// 4x4 matrix representation of the transformation
    /// Can be null, if the transformation cannot be expressed as a 4x4 matrix
    /// </summary>
    virtual glm::mat4 GetMatrix() const  = 0;

    /// <summary>
    /// 4x4 matrix representation of the inverse transformation
    /// Can be null, if the inverse transformation cannot be expressed as a 4x4 matrix
    /// </summary>
    virtual glm::mat4 GetMatrixInverse() const  = 0;

    /// <summary>
    /// Create a copy of the present object
    /// </summary>
    //virtual ITransformation Clone { get; }

protected:
	ITransformation() {}
	virtual ~ITransformation() {}
};

    //class MatrixTransformation : GenericMatrixTransformation
    //{
    //    private readonly Matrix4x4 _tfMat;
    //    private readonly Matrix4x4 _tfMatInv;

    //    /// <summary>
    //    /// Constructor
    //    /// </summary>
    //    public MatrixTransformation()
    //    {
    //        _tfMat = Matrix4x4.Identity();
    //        _tfMatInv = Matrix4x4.Identity();
    //    }

    //    /// <summary>
    //    /// Constructor
    //    /// </summary>
    //    /// <param name="matrix">The Transformation's matrix and inverse matrix will be initialized using this matrix</param>
    //    public MatrixTransformation(Matrix4x4 matrix)
    //    {
    //        _tfMat = new Matrix4x4(matrix);
    //        _tfMatInv = matrix.Inverted();
    //    }

    //    /// <summary>
    //    /// Constructor
    //    /// </summary>
    //    /// <param name="matrix"></param>
    //    /// <param name="matrixInv"></param>
    //    public MatrixTransformation(Matrix4x4 matrix, Matrix4x4 matrixInv)
    //    {
    //        Debug.Assert(matrix * matrixInv == Matrix4x4.Identity());
    //        _tfMat = new Matrix4x4(matrix);
    //        _tfMatInv = new Matrix4x4(matrixInv);
    //    }

    //    /// <summary>
    //    /// Transformation matrix
    //    /// </summary>
    //    public override Matrix4x4 Matrix
    //    {
    //        get { return _tfMat; }
    //    }

    //    /// <summary>
    //    /// Inverse transformation matrix
    //    /// </summary>
    //    public override Matrix4x4 MatrixInverse
    //    {
    //        get { return _tfMatInv; }
    //    }

    //    /// <summary>
    //    /// Create a copy of the present object
    //    /// </summary>
    //    public override ITransformation Clone
    //    {
    //        get { return new MatrixTransformation(Matrix, MatrixInverse); }
    //    }
    //};

class GenericMatrixTransformation : public ITransformation
{

    glm::vec3 Transform(const glm::vec3& point) const override
	{
		return glm::vec3( GetMatrix() * glm::vec4( point,0.0f) );
	}


    glm::vec3 TransformInverse(glm::vec3 point) const override 
	{
		return glm::vec3( GetMatrixInverse() * glm::vec4( point,0.0f) );
    }


 //   /// <summary>
 //   /// Transform a Vector with the inverse Transformation
 //   /// </summary>
 //   /// <param name="c">Vector to be transformed</param>
 //   /// <returns></returns>
 //   public glm::vec3 TransformInverse(Vector3d c)
 //   {
 //       return GetMatrixInverse() * c;
 //   }

 //   /// <summary>
 //   /// inverted transformation
 //   /// </summary>
 //   public ITransformation Inverse
 //   {
 //       get { return new MatrixTransformation(MatrixInverse, Matrix); }
 //   }

 //   /// <summary>
 //   /// multiplication of two transformations
 //   /// </summary>
 //   /// <param name="a"></param>
 //   /// <param name="b"></param>
 //   /// <returns></returns>
 //   public static MatrixTransformation operator *(GenericMatrixTransformation a, GenericMatrixTransformation b)
 //   {
 //       return new MatrixTransformation(
 //           b.Matrix * a.Matrix,
 //           a.MatrixInverse * b.MatrixInverse);
 //   }

 //   /// <summary>
 //   /// Transformation matrix
 //   /// </summary>
	//virtual glm::mat4 GetMatrix() const 

 //   /// <summary>
 //   /// Inverse transformation matrix
 //   /// </summary>
 //   public abstract glm::mat4 MatrixInverse { get; }


    /// <summary>
    /// Create a copy of the present object
    /// </summary>
    //public abstract ITransformation Clone { get; }
protected:
	GenericMatrixTransformation(){};
	~GenericMatrixTransformation(){};

};

static const float ssgEpsilon = 1e-6f;

class RigidTransformation : public GenericMatrixTransformation
{
private:
	glm::vec3 _scale;
	glm::mat4 _rotation;
	glm::vec3 _translation;

public:
	RigidTransformation()
		:_scale(1, 1, 1)
		,_translation(0, 0, 0)
	{
	}

	virtual ~RigidTransformation()
	{
	}

	glm::vec3 GetTranslationVector() const { return _translation; }
	void SetTranslationVector(const glm::vec3& value ){ _translation = value; }

    glm::vec3 GetScaleVector() const { return _scale; }
	void SetScaleVector(const glm::vec3& value ){ 
		assert( fabs(value.x) > ssgEpsilon);
		assert( fabs(value.y) > ssgEpsilon);
		assert( fabs(value.z) > ssgEpsilon);
		_scale = value; 
	}

	glm::mat4 GetRotationMatrix() const { return _rotation; }
	void SetRotationMatrix(const glm::mat4& value ){ _rotation = value; }

    glm::mat4 GetMatrix() const override 
    {
		glm::mat4 trans = glm::translate(glm::mat4(),_translation);
		glm::mat4 scale= glm::scale(glm::mat4(), _scale);
		return trans * _rotation * scale;
    }

	glm::mat4 GetMatrixInverse() const override 
	{
		glm::mat4 trans = glm::translate(glm::mat4(),-_translation);
		glm::mat4 scale= glm::scale(glm::mat4(), 1.0f/_scale);
		return scale * _rotation * trans;
	}


    glm::vec3 Transform(const glm::vec3& point) const override
	{
		return glm::vec3();
	}

    /// <summary>
    /// Transform a point with the inverse Transformation
    /// </summary>
    /// <param name="point">Point in child space to be transformed to parent space</param>
    /// <returns>Transformed location</returns>
    glm::vec3 TransformInverse(glm::vec3 point) const override
	{
		return glm::vec3();
	}

 //   /// <summary>
 //   /// Create a copy of the present object
 //   /// </summary>
 //   //public override ITransformation Clone
 //   //{ 
 //   //    get
 //   //    {
 //   //        var transformation = new RigidTransformation
 //   //        {
 //   //            ScaleVector = ScaleVector,
 //   //            TranslationVector = TranslationVector,
 //   //            RotationMatrix = new Matrix4x4(RotationMatrix)
 //   //        };
 //   //        return transformation;
 //   //    }
 //   //}

 //
	//void SetRigidTransformationFromMatrix(const glm::mat4& matrix)
	//{
	//	_scale = glm::vec3(	glm::column(matrix,0).length(),
	//						glm::column(matrix,1).length(),
	//						glm::column(matrix,2).length() );
	//	RotationMatrix = glm::extractMatrixRotation( matrix );
	//	_translation = (glm::vec3)glm::row(matrix,3);
	//}
};

//
//
////class ssg
////{
////public:
////	ssg(void);
////	~ssg(void);
////};
//
//
//
//
//
//
////abstract 

//
//
//
///// <summary>
///// Rigid coordinate space transformation (translation * rotation * scaling)
///// </summary>
//

//
//
//
//
//
////class SsgTransformation
////{
////public:
////	SsgTransformation();
////	SsgTransformation(const glm::mat4& matrix);
////	SsgTransformation(const SsgTransformation& rhs );
////	SsgTransformation& operator=(SsgTransformation other ) { swap(other); return *this; }
////	SsgTransformation(SsgTransformation&& other ) { swap(other); }
////
////	glm::mat4 GetMatrix() const {return _matrix;}
////	glm::mat4 GetMatrixInverse() const {return _matrixInverse;}
////	glm::vec3 GetTranslationVector() const;
////	glm::vec3 GetScaleVector() const;
////	glm::mat4 GetRotationMatrix() const;
////	
////	glm::vec3 Transform(const glm::vec3& vector);
////	glm::vec3 TransformInverse(const glm::vec3& vector);
////
////	void Multiply(const SsgTransformation& transformation);
////	void RotateAxis(float angle,const glm::vec3& axis);
////	void Translate(const glm::vec3& deltaTranslation);
////	void Scale(const glm::vec3& scaling);
////
////private:
////	void swap(SsgTransformation& other) 
////	{
////		std::swap( _matrix, other._matrix );
////		std::swap( _matrixInverse, other._matrixInverse );
////	}
////
////	glm::mat4   _matrix;
////	glm::mat4   _matrixInverse;
////};
////
////
////class SsgSpace
////{
////public:
////	SsgSpace();
////	SsgSpace(const std::string& name);
////
////
////private:
////	std::list<SsgSpace> _children;
////	std::string         _name;
////};
//

#endif

