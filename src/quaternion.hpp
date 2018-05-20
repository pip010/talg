#include "vector.hpp"
#include "matrix.hpp"

namespace talg
{

  template<typename T>
  struct TQuaternion : public TVector<4,T,vtag_xyzw>
  {

    //inherit cnstr
    using TVector<4,T,vtag_xyzw>::TVector;

    //forward brace initializer
    using TVector<4,T,vtag_xyzw>::data;
    using TVector<4,T,vtag_xyzw>::x;
    using TVector<4,T,vtag_xyzw>::y;
    using TVector<4,T,vtag_xyzw>::z;
    using TVector<4,T,vtag_xyzw>::w;

    //TODO from HomoMatrix
    void FromRotationMatrix(TMatrix<3,3,T> rotm)
    {
      // Adapted from Ogre3D OgreQuaternion.h/cpp

      // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
      // article "Quaternion Calculus and Fast Animation".

      T fTrace = trace(rotm);
      T fRoot;

      if ( fTrace > 0.0 )
      {
          // |w| > 1/2, may as well choose w > 1/2
          fRoot = sqrt(fTrace + 1.0f);  // 2w
          w = 0.5f*fRoot;
          fRoot = 0.5f/fRoot;  // 1/(4w)
          x = (rotm[2][1]-rotm[1][2])*fRoot;
          y = (rotm[0][2]-rotm[2][0])*fRoot;
          z = (rotm[1][0]-rotm[0][1])*fRoot;
      }
      else
      {
          // |w| <= 1/2
          static size_t s_iNext[3] = { 1, 2, 0 };
          size_t i = 0;
          //if ( kRot[1][1] > kRot[0][0] )
          //    i = 1;
          //if ( kRot[2][2] > kRot[i][i] )
          //    i = 2;
          i = rotm[1][1] > rotm[0][0] ? 1 : i;
          i = rotm[2][2] > rotm[i][i] ? 2 : i;
          size_t j = s_iNext[i];
          size_t k = s_iNext[j];

          fRoot = sqrt(rotm[i][i]-rotm[j][j]-rotm[k][k] + 1.0f);
          T* apkQuat[3] = { &x, &y, &z };
          *apkQuat[i] = 0.5f*fRoot;
          fRoot = 0.5f/fRoot;
          w = (rotm[k][j]-rotm[j][k])*fRoot;
          *apkQuat[j] = (rotm[j][i]+rotm[i][j])*fRoot;
          *apkQuat[k] = (rotm[k][i]+rotm[i][k])*fRoot;
      }

    }

    //TODO homo HomoMatrix
    TMatrix<3,3,T> ToRotationMatrix() const
    {
      // Adapted from Ogre3D OgreQuaternion.h/cpp

        TMatrix<3,3,T> rotm;

        T fTx  = x+x;
        T fTy  = y+y;
        T fTz  = z+z;
        T fTwx = fTx*w;
        T fTwy = fTy*w;
        T fTwz = fTz*w;
        T fTxx = fTx*x;
        T fTxy = fTy*x;
        T fTxz = fTz*x;
        T fTyy = fTy*y;
        T fTyz = fTz*y;
        T fTzz = fTz*z;

        rotm[0][0] = 1.0f-(fTyy+fTzz);
        rotm[0][1] = fTxy-fTwz;
        rotm[0][2] = fTxz+fTwy;
        rotm[1][0] = fTxy+fTwz;
        rotm[1][1] = 1.0f-(fTxx+fTzz);
        rotm[1][2] = fTyz-fTwx;
        rotm[2][0] = fTxz-fTwy;
        rotm[2][1] = fTyz+fTwx;
        rotm[2][2] = 1.0f-(fTxx+fTyy);

        return rotm;
    }


      void FromAxes (TVector<3,T> akAxis)
      {
          TMatrix<3,3,T> kRot;

          for (int i = 0; i < 3; ++i)
          {
              kRot[0][i] = akAxis[i].x;
              kRot[1][i] = akAxis[i].y;
              kRot[2][i] = akAxis[i].z;
          }

          FromRotationMatrix(kRot);
      }

      void FromAxes (TVector<3,T> xaxis, TVector<3,T> yaxis, const TVector<3,T>& zaxis)
      {
          TMatrix<3,3,T> kRot;

          kRot[0][0] = xaxis.x;
          kRot[1][0] = xaxis.y;
          kRot[2][0] = xaxis.z;

          kRot[0][1] = yaxis.x;
          kRot[1][1] = yaxis.y;
          kRot[2][1] = yaxis.z;

          kRot[0][2] = zaxis.x;
          kRot[1][2] = zaxis.y;
          kRot[2][2] = zaxis.z;

          FromRotationMatrix(kRot);
      }

      TVector<3,T> ToAxes () const
      {
          TVector<3,T> akAxis;

          auto kRot= ToRotationMatrix();

          for (int i = 0; i < 3; ++i)
          {
              akAxis[i].x = kRot[0][i];
              akAxis[i].y = kRot[1][i];
              akAxis[i].z = kRot[2][i];
          }

          return akAxis;
      }

  };// end TQuaternion


  //Build a unit quaternion representing the rotation
  //from u to v. The input vectors need not be normalised.
  template<typename T>
  TQuaternion<T> fromTwoVectors()
  {
    //https://bitbucket.org/sinbad/ogre/pull-requests/308/some-vector-quaternion-routines/diff
    //http://lolengine.net/blog/2014/02/24/quaternion-from-two-vectors-final


    /*
    float norm_u_norm_v = sqrt(dot(u, u) * dot(v, v));
    float real_part = norm_u_norm_v + dot(u, v);
    vec3 w;

    if (real_part < 1.e-6f * norm_u_norm_v)
    {
        //If u and v are exactly opposite, rotate 180 degrees
        //around an arbitrary orthogonal axis. Axis normalisation
        //can happen later, when we normalise the quaternion.
        real_part = 0.0f;
        w = abs(u.x) > abs(u.z) ? vec3(-u.y, u.x, 0.f)
                                : vec3(0.f, -u.z, u.y);
    }
    else
    {
        // Otherwise, build quaternion the standard way.
        w = cross(u, v);
    }

    return normalize(quat(real_part, w.x, w.y, w.z));
    */
    return {0,0,0,1};
  }


}//end namespace
