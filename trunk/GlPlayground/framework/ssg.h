#ifndef SSG_H_INCLUDED
#define SSG_H_INCLUDED

#include <list>
#include <cassert>
#include <string>
#include <vector>
#include <memory>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace SSG{

class Transformation
{
private:
	glm::mat4 m_tfMat;
	glm::mat4 m_tfMatInv;

public:
	Transformation(){}

	Transformation(const Transformation& other)
	{
		m_tfMat    = other.m_tfMat;
		m_tfMatInv = other.m_tfMatInv;
	}

	Transformation(const glm::mat4& matrix)
	{
		m_tfMat = matrix;
		m_tfMatInv = glm::inverse( matrix );
	}

	Transformation(const glm::mat4& matrix, const glm::mat4& matrixInv)
	{
		m_tfMat = matrix;
		m_tfMatInv = matrixInv;
	}


	void Reset()
	{
		m_tfMat = glm::mat4();
		m_tfMatInv = glm::mat4();
	}


	Transformation Inverted()
	{
		return Transformation(m_tfMatInv, m_tfMat);
	}

	glm::vec3 GetTranslationVector() 
	{
		return (glm::vec3)glm::row(m_tfMat,0);
	}

	glm::vec3 GetScaleVector()
	{
		return glm::vec3(	
			glm::column(m_tfMat,0).length(),
			glm::column(m_tfMat,1).length(),
			glm::column(m_tfMat,2).length() );
	}

	Transformation GetRotationMatrix()
	{
		glm::vec3 scaleVector = GetScaleVector();
		glm::mat4 mat;
		mat[0, 0] = m_tfMat[0, 0] / scaleVector.x;
		mat[0, 1] = m_tfMat[0, 1] / scaleVector.y;
		mat[0, 2] = m_tfMat[0, 2] / scaleVector.z;

		mat[1, 0] = m_tfMat[1, 0] / scaleVector.x;
		mat[1, 1] = m_tfMat[1, 1] / scaleVector.y;
		mat[1, 2] = m_tfMat[1, 2] / scaleVector.z;

		mat[2, 0] = m_tfMat[2, 0] / scaleVector.x;
		mat[2, 1] = m_tfMat[2, 1] / scaleVector.y;
		mat[2, 2] = m_tfMat[2, 2] / scaleVector.z;
		return Transformation(mat);
	}

	glm::vec3 Transform(const glm::vec3& vector) const
	{
		return glm::vec3( m_tfMat * glm::vec4(vector, 1.0f ));
	}

	glm::vec3 TransformInv(const glm::vec3& vector) const
	{
		return glm::vec3( m_tfMatInv * glm::vec4(vector, 1.0f ));
	}

	void Mul(const Transformation& t)
	{
		m_tfMat = t.m_tfMat * m_tfMat;
		m_tfMatInv = m_tfMatInv * t.m_tfMatInv;
	}

	//static Transformation operator*(const Transformation& a, const Transformation& b)
	//{
	//	Transformation t(a);
	//	t.Mul(b);
	//	return t;
	//}

	void RotateAxis(const glm::vec3& axis, float angle)
	{
		m_tfMat = glm::rotate(glm::mat4(), angle * 180.0f / 3.1415926f, axis) * m_tfMat;
		m_tfMatInv = m_tfMatInv * glm::rotate(-angle * 180.0f / 3.1415926f, axis);
	}

	void Translate(const glm::vec3& delta)
	{
		auto tm = glm::mat4();
		tm[3] = glm::vec4(delta, 1.0f);
		m_tfMat = tm * m_tfMat;

		tm[3] = glm::vec4(-delta, 1.0f);
		m_tfMatInv = m_tfMatInv * tm;
	}

	void Scale(const glm::vec3& scale)
	{
		m_tfMat = glm::scale(glm::mat4(),scale) * m_tfMat;
		m_tfMatInv = m_tfMatInv * glm::scale(glm::mat4(),scale);
	}


	glm::mat4 GetMatrix()
	{
		return m_tfMat;
	}

	glm::mat4 GetMatrixInverse()
	{
		return m_tfMatInv;
	}



	/// <summary>
	/// Transform vector v from SceneSpace 'from' to SceneSpace 'to'
	/// </summary>
	/// <param name="v">Vector to be transformed</param>
	/// <param name="from">The SceneSpace in which v is defined</param>
	/// <param name="to">The SceneSpace to which v will be transformed</param>
	/// <returns>Transformed vector</returns>
};

class SceneSpace
{
private:
	bool							_isValid;
	std::vector<SceneSpace*>		m_children;
	std::string						m_name;
	mutable Transformation			m_transToRoot;
	Transformation					m_transToParent;
	SceneSpace*						m_parent;
	

public:
	SceneSpace(SceneSpace* const parent)
		: _isValid( true )
		,m_parent(parent)
	{
		if ( parent != nullptr) m_parent->ChildAdd(this);
	}
	SceneSpace(const SceneSpace& parent)
		: _isValid( true )
	{
		m_parent = (SceneSpace*)&parent;
		m_parent->ChildAdd(this);
	}

	~SceneSpace()
	{
	}
    
	std::string GetName() const { return m_name; }
	void SetName(const std::string& value) { m_name = value; }

    void SetTransformationToParent(const Transformation& t)
    {
        if (m_parent != nullptr)
        {
            m_transToParent = t;
            InvalidateTrans();
        }
    }


	void Translate(const glm::vec3& value)
	{
		m_transToParent.Translate(value);
		InvalidateTrans();
	}
	void Scale(const glm::vec3& value)
	{
		m_transToParent.Scale(value);
		InvalidateTrans();
	}
	void RotateAxis(const glm::vec3& axis, float angle)
	{
		m_transToParent.RotateAxis(axis, angle );
		InvalidateTrans();
	}

    Transformation& GetTransformationToParent()
    {
		return m_transToParent;
    }

	Transformation GetTransformationToSpace(SceneSpace& other)
    {

        if (&other == this)
        {
            return Transformation();
        }
		else if (other.m_parent == nullptr)
        {
            return GetTransformationToRoot();
        }

        else if (m_parent == nullptr)
        {
            return other.GetTransformationToRoot().Inverted();
        }
        else
        {
            return Transformation(
                other.GetTransformationToRoot().GetMatrixInverse() * GetTransformationToRoot().GetMatrix(),
                GetTransformationToRoot().GetMatrixInverse() * other.GetTransformationToRoot().GetMatrix() );
        }
        }
        
        void Reset()
        {
            InvalidateTrans();
        }

        bool IsTransformationInvalid()
        {
			return !_isValid;
        }        

        Transformation GetTransformationToRoot() const
        {   
			if ( !_isValid )
			{
				m_transToRoot.Reset();
                m_transToRoot.Mul(m_transToParent);
				if (m_parent != nullptr )
					m_transToRoot.Mul(m_parent->GetTransformationToRoot());
			}
            return Transformation(m_transToRoot);
        }

        SceneSpace&  GetParent()
        {
            return *m_parent;
        }

	static glm::vec3 Transform(const glm::vec3& vector, const SceneSpace& fromSpace, const SceneSpace& toSpace)
	{
		auto rootPos = fromSpace.GetTransformationToRoot().Transform(vector);
		return toSpace.GetTransformationToRoot().TransformInv(rootPos);
	}

	//class Coord3;

//	SetPosition( const Coord3* const pos);

protected :
    void ChildAdd(SceneSpace* o)
    {
		m_children.push_back(o);
    }

	void ChildRem(SceneSpace* o)
    {
        //Debug.Assert(o != null);
        //if (m_children.Contains(o)) { m_children.Remove(o); }
    }

        /// <summary>
        /// Get array of children attached to this parent.
        /// </summary>
        /// <returns>Array of SceneSpaces</returns>
        //public SceneSpace[] Children
        //{
        //    get
        //    {
        //        SceneSpace[] sa = new SceneSpace[m_children.Count];
        //        m_children.CopyTo(sa, 0);

        //        return sa;
        //    }
        //}

        /// <summary>
        /// Invalidate the transformation object that 
        /// holds the transformation to the root scene.
        /// </summary>
	void InvalidateTrans()
	{
		if (!_isValid) return;
		_isValid= false; 

		for ( auto child : m_children)
		{
			if (child != nullptr) 
			{ 
				child->InvalidateTrans(); 
			}
		}
	}

	Transformation const GetTransToParent() { return Transformation(m_transToParent); }
    
	void SetTransToParent(const Transformation& value ) 
	{ 
		m_transToParent = value; 
	}
};


class Coord3 
{
public:
	Coord3(const SceneSpace& mySpace, double x, double y, double z)
		: m_mySpace( &mySpace )
		, m_position( glm::vec3(x,y,z) ) { }

	Coord3(const SceneSpace& mySpace, const glm::vec3& vec)
		: m_mySpace( &mySpace )
		, m_position( vec )  { }

	Coord3(const Coord3& other)
		: m_mySpace( other.m_mySpace )
		, m_position( other.m_position ) { }

	Coord3& operator=(const Coord3& other ) 
	{
		m_mySpace = other.m_mySpace;
		m_position = other.m_position;
		return *this; 
	}

	const SceneSpace& GetSpace() const
	{
		return *m_mySpace;
	}

    glm::vec3 Get(const SceneSpace& toSpace) const
    {
        //if ( toSpace == m_mySpace) { return new glm::vec3(m_position); }
        return SceneSpace::Transform(m_position, *m_mySpace, toSpace);
    }


    Coord3 InSpace(const SceneSpace& toSpace) const
    {
        return Coord3(toSpace, Get(toSpace));
    }

	//Coord3 example::operator+(const Coord3& other)
	//{
	//	return new Coord3(coord.MySpace, coord.m_position + dir.Get(coord.MySpace));

 //   example tmp_obj = *this;
 //   tmp_obj.a = tmp_obj.a + obj2.a;
 //   tmp_obj.b = tmp_obj.b + obj2.b;
 //   return tmp_obj;
	//}

	//public static Coord3 operator +(Coord3 coord, IDir3 dir)
 //       {
 //           return new Coord3(coord.MySpace, coord.m_position + dir.Get(coord.MySpace));
 //       }

 //       /// <summary>
 //       /// Subtract a direction vector from a point
 //       /// </summary>
 //       /// <param name="coord">point</param>
 //       /// <param name="dir">direction vector</param>
 //       /// <returns>coord - dir</returns>
 //       public static Coord3 operator -(Coord3 coord, IDir3 dir)
 //       {
 //           return new Coord3(coord.MySpace, coord.m_position - dir.Get(coord.MySpace));
 //       }

        /// <summary>
        /// Subtract a point from another point, delivering a direction vector
        /// </summary>
        /// <param name="coord1">head</param>
        /// <param name="coord2">tail</param>
        /// <returns>coord1 - coord2</returns>
        //public static Dir3 operator -(Coord3 coord1, ICoord3 coord2)
        //{
        //    return new Dir3(coord1.MySpace, coord2.Get(coord1.MySpace), coord1.Get(coord1.MySpace));
        //}
private:
		const SceneSpace* 	m_mySpace;
		glm::vec3			m_position;

};



//
//class Dir3
//{
//	private:
//		const SceneSpace&  m_mySpace;
//        glm::vec3	m_from;
//        glm::vec3	m_to;
//
//        /// <summary>
//        /// Constructor that takes a tail and head coordinate
//        /// </summary>
//        /// <param name="mySpace">The space in which this direction is defined</param>
//        /// <param name="from">tail</param>
//        /// <param name="to">head</param>
//        public Dir3(const SceneSpace& mySpace, glm::vec3 from, glm::vec3 to)
//			: m_mySpace( mySpace )
//			, 
//        {
//            m_mySpace = mySpace;
//            m_from = from;
//            m_to = to;
//        }
//
//        /// <summary>
//        /// Constructor that takes a tail and head coordinate
//        /// </summary>
//        /// <param name="mySpace">The space in which this direction is defined</param>
//        /// <param name="from">tail</param>
//        /// <param name="to">head</param>
//        public Dir3(SceneSpace mySpace, ICoord3 from, ICoord3 to)
//        {
//            m_mySpace = mySpace;
//            m_from = from.Get(mySpace);
//            m_to = to.Get(mySpace);
//        }
//
//        /// <summary>
//        /// Constructor that takes a direction vector
//        /// </summary>
//        /// <param name="mySpace">The space in which this direction is defined</param>
//        /// <param name="direction">vector</param>
//        public Dir3(SceneSpace mySpace, glm::vec3 direction)
//        {
//            m_mySpace = mySpace;
//            m_from = new glm::vec3(0.0);
//            m_to = direction;
//        }
//
//        /// <summary>
//        /// Constructor that takes an IDir3 as argument
//        /// </summary>
//        /// <param name="dir">IDir3 instance</param>
//        public Dir3(IDir3 dir)
//        {
//            m_mySpace = dir.MySpace;
//            m_from = dir.From.Get(m_mySpace);
//            m_to = dir.To.Get(m_mySpace);
//        }
//
//        /// <summary>
//        /// The space in which this direction is defined
//        /// </summary>
//        public SceneSpace MySpace { get { return m_mySpace; } }
//
//        /// <summary>
//        /// The from vector defined in myspace
//        /// </summary>
//        public ICoord3 From { get { return new Coord3(m_mySpace, m_from); } }
//
//        /// <summary>
//        /// The to vector defined in myspace
//        /// </summary>
//        public ICoord3 To { get { return new Coord3(m_mySpace, m_to); } }
//
//        /// <summary>
//        /// Calculate direction for supplied space
//        /// </summary>
//        /// <param name="toSpace">Space for which direction is calculated</param>
//        /// <returns>Direction in space 'toSpace'</returns>
//        public glm::vec3 Get(SceneSpace toSpace)
//        {
//            glm::vec3 from = new glm::vec3(m_from);
//            glm::vec3 to = new glm::vec3(m_to);
//
//            if (toSpace != m_mySpace)
//            {
//                from = Transformation.Transform(m_from, m_mySpace, toSpace);
//                to   = Transformation.Transform(m_to, m_mySpace, toSpace);
//            }
//
//            return new glm::vec3(to - from);
//        }
//
//        /// <summary>
//        /// Transform the direction to an arbitrary SceneSpace
//        /// </summary>
//        /// <param name="toSpace"></param>
//        /// <returns></returns>
//        public IDir3 InSpace(SceneSpace toSpace)
//        {
//            return new Dir3(toSpace, From, To);
//        }
//
//        /// <summary>
//        /// Invert direction
//        /// </summary>
//        /// <param name="d">Direction to be inverted</param>
//        /// <returns>Inverse of d</returns>
//        public static Dir3 operator -(Dir3 d)
//        {
//            SceneSpace space = d.MySpace;
//            glm::vec3 from = d.From.Get(space);
//            glm::vec3 to = d.To.Get(space);
//            return new Dir3(space, from, from - to);
//        }
//
//        /// <summary>
//        /// Scale the direction with a scalar
//        /// </summary>
//        /// <param name="mult">scalar</param>
//        /// <param name="d">direction</param>
//        /// <returns>mult * d</returns>
//        public static Dir3 operator *(double mult, Dir3 d)
//        {
//            return new Dir3(d.MySpace, d.m_from, d.m_from + mult * (d.m_to - d.m_from));
//        }
//
//        /// <summary>
//        /// Add two direction vectors
//        /// </summary>
//        /// <param name="d1">first vector</param>
//        /// <param name="d2">second vector</param>
//        /// <returns>d1 + d2</returns>
//        public static Dir3 operator +(Dir3 d1, IDir3 d2)
//        {
//            SceneSpace space1 = d1.MySpace;
//            glm::vec3 vec = d1.Get(space1) + d2.Get(space1);
//            return new Dir3(space1, d1.m_from, d1.m_from + vec);
//        }
//
//        /// <summary>
//        /// Subtract a direction vector from another one
//        /// </summary>
//        /// <param name="d1">first vector</param>
//        /// <param name="d2">second vector</param>
//        /// <returns>d1 - d2</returns>
//        public static Dir3 operator -(Dir3 d1, IDir3 d2)
//        {
//            SceneSpace space1 = d1.MySpace;
//            glm::vec3 vec = d1.Get(space1) - d2.Get(space1);
//            return new Dir3(space1, d1.m_from, d1.m_from + vec);
//        }
//    }

};


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
//    private readonly glm::mat4 _tfMat;
//    private readonly glm::mat4 _tfMatInv;

//    /// <summary>
//    /// Constructor
//    /// </summary>
//    public MatrixTransformation()
//    {
//        _tfMat = glm::mat4.Identity();
//        _tfMatInv = glm::mat4.Identity();
//    }

//    /// <summary>
//    /// Constructor
//    /// </summary>
//    /// <param name="matrix">The Transformation's matrix and inverse matrix will be initialized using this matrix</param>
//    public MatrixTransformation(glm::mat4 matrix)
//    {
//        _tfMat = new glm::mat4(matrix);
//        _tfMatInv = matrix.Inverted();
//    }

//    /// <summary>
//    /// Constructor
//    /// </summary>
//    /// <param name="matrix"></param>
//    /// <param name="matrixInv"></param>
//    public MatrixTransformation(glm::mat4 matrix, glm::mat4 matrixInv)
//    {
//        Debug.Assert(matrix * matrixInv == glm::mat4.Identity());
//        _tfMat = new glm::mat4(matrix);
//        _tfMatInv = new glm::mat4(matrixInv);
//    }

//    /// <summary>
//    /// Transformation matrix
//    /// </summary>
//    public override glm::mat4 Matrix
//    {
//        get { return _tfMat; }
//    }

//    /// <summary>
//    /// Inverse transformation matrix
//    /// </summary>
//    public override glm::mat4 MatrixInverse
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
	//   public glm::vec3 TransformInverse(glm::vec3 c)
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
	//   //            RotationMatrix = new glm::mat4(RotationMatrix)
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


//
//class SsgScene
//{
//private:
//    bool _disposed;
//    Space _root;                
//
//public :
//    Scene()
//	{
//        _root = new RigidSpace(this) { Name = "RootSpace" };
//	}
//        
//    /// <summary>
//    /// Destructor
//    /// </summary>
//    ~Scene()
//    {
//        Dispose(false);
//    }
//
//    /// <summary>
//    /// Invalidate complete scene.
//    /// 
//    /// Calling this method on the scene object will 
//    /// trigger a transformation changed event on the entire tree.
//    /// </summary>
//    public virtual void Invalidate()
//    {
//        _root.Invalidate();
//    }
//        
//    /// <summary>
//    /// Deterministic cleaning of resources
//    /// </summary>
//    public void Dispose()
//    {
//        Dispose(true);
//        GC.SuppressFinalize(this);
//    }
//
//    /// <summary>
//    /// Dispose implementation
//    /// </summary>
//    /// <param name="disposing"></param>
//    protected virtual void Dispose(bool disposing)
//    {
//        if(!IsDisposed)
//        {
//            if(disposing)
//            {
//                _root.Dispose();
//                _root = null;
//            }
//        }
//            
//        _disposed = true;
//    }
//
//    /// <summary>
//    /// Has this object been disposed?
//    /// </summary>
//    public bool IsDisposed
//    {
//        get { return _disposed; }
//    }
//
//    /// <summary>
//    /// Return the root space of this scene.
//    /// </summary>
//    public Space Root
//    {
//        get { return _root; }
//    }
//};

#endif

