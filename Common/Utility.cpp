
#include "Utility/Utility.h"



D3DMATRIX toD3DMatrix(const Matrix4 &mat)
{
    // 转置矩阵
    // D3D9 使用行向量 i.e. V*M
    // Tiny3D, OpenGL 等用列向量 i.e. M*V
    D3DXMATRIX d3dMat;
    d3dMat.m[0][0] = mat[0][0];
    d3dMat.m[0][1] = mat[1][0];
    d3dMat.m[0][2] = mat[2][0];
    d3dMat.m[0][3] = mat[3][0];

    d3dMat.m[1][0] = mat[0][1];
    d3dMat.m[1][1] = mat[1][1];
    d3dMat.m[1][2] = mat[2][1];
    d3dMat.m[1][3] = mat[3][1];

    d3dMat.m[2][0] = mat[0][2];
    d3dMat.m[2][1] = mat[1][2];
    d3dMat.m[2][2] = mat[2][2];
    d3dMat.m[2][3] = mat[3][2];

    d3dMat.m[3][0] = mat[0][3];
    d3dMat.m[3][1] = mat[1][3];
    d3dMat.m[3][2] = mat[2][3];
    d3dMat.m[3][3] = mat[3][3];

    return d3dMat;
}

Matrix4 toT3DMatrix(const D3DMATRIX &mat)
{
    Matrix4 t3dMat;
    t3dMat[0][0] = mat.m[0][0];
    t3dMat[1][0] = mat.m[0][1];
    t3dMat[2][0] = mat.m[0][2];
    t3dMat[3][0] = mat.m[0][3];

    t3dMat[0][1] = mat.m[1][0];
    t3dMat[1][1] = mat.m[1][1];
    t3dMat[2][1] = mat.m[1][2];
    t3dMat[3][1] = mat.m[1][3];

    t3dMat[0][2] = mat.m[2][0];
    t3dMat[1][2] = mat.m[2][1];
    t3dMat[2][2] = mat.m[2][2];
    t3dMat[3][2] = mat.m[2][3];

    t3dMat[0][3] = mat.m[3][0];
    t3dMat[1][3] = mat.m[3][1];
    t3dMat[2][3] = mat.m[3][2];
    t3dMat[3][3] = mat.m[3][3];

    return t3dMat;
}

Matrix4 lookAt(const Vector3 &pos, const Vector3 &obj, const Vector3 &up)
{
    Vector3 N = obj - pos;
    N.normalize();
    Vector3 V = up;
    V.normalize();
    Vector3 U = N.cross(V);
    U.normalize();
    V = U.cross(N);

    Matrix4 mat(false);
    mat[0][0] = U.x();
    mat[0][1] = U.y();
    mat[0][2] = U.z();
    mat[1][0] = V.x();
    mat[1][1] = V.y();
    mat[1][2] = V.z();
    mat[2][0] = -N.x();
    mat[2][1] = -N.y();
    mat[2][2] = -N.z();
    mat[0][3] = -U.dot(pos);
    mat[1][3] = -V.dot(pos);
    mat[2][3] = N.dot(pos);
// 
//     return mat;
    Matrix3 m3;
    m3.setColumn(0, U);
    m3.setColumn(1, V);
    m3.setColumn(2, -N);
    Quaternion q(m3);

    Transform transform(pos, Vector3(1.0, 1.0, 1.0), q);
//     Vector3 t = transform.getTranslate();
//     Quaternion orientation = transform.getOrientation();
//     Matrix3 m;
//     orientation.toRotationMatrix(m);
//     Matrix4 m4(m);
//     m[0][3] = -Vector3(.dot(t);
//     Matrix4 m = transform.getAffineMatrix();
//     m[0][3] = -m[0][3];
//     m[1][3] = -m[1][3];
//     m[2][3] = -m[2][3];
    Matrix4 matRot(transform.getOrientation());
    Matrix4 mr = matRot.transpose();
    Matrix4 mt(false);
    mt.makeTranslate(-transform.getTranslate());
    Matrix4 m = mr * mt;
    return m;
}

Matrix4 perpective(const Radian &rkFovY, Real aspect, Real nearDist, Real farDist)
{
    // 透视投影
    Real tanThetaY = Math::Tan(rkFovY * Real(0.5));
    Real h = Real(1.0) / (tanThetaY);
    Real w = h / aspect;            
    Real q = farDist / (nearDist - farDist);
    Real qn = nearDist * q;

    Matrix4 mat;
    mat.makeZero();
    mat[0][0] = w;
    mat[1][1] = h;
    mat[2][2] = q;
    mat[2][3] = qn;
    mat[3][2] = -1.0;

    return mat;
}

Matrix4 ortho(const Radian &rkFovY, Real ratio, Real nearDist, Real farDist)
{
    Real tanThetaY = Math::Tan(rkFovY * Real(0.5));
    Real h = Real(1.0) / (nearDist * tanThetaY);
    Real w = h / ratio;
    Real q = Real(1.0) / (nearDist - farDist);
    Real qn = nearDist * q;

    Matrix4 mat;
    mat.makeZero();
    mat[0][0] = w;
    mat[1][1] = h;
    mat[2][2] = q;
    mat[2][3] = qn;
    mat[3][3] = 1.0;
    return mat;
}