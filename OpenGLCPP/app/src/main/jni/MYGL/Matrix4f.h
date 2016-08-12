//
// Created by redknot on 8/12/16.
//

#ifndef OPENGLCPP_MATRIX4F_H
#define OPENGLCPP_MATRIX4F_H



class Matrix4f {
private:
public:
    float mat[4][4];
    inline Matrix4f operator * (Matrix4f& Right)
    {
        Matrix4f Ret;

        for(unsigned int i=0;i<4;i++)
        {
            for(unsigned int j=0;j<4;j++)
            {
                Ret.mat[i][j] = mat[i][0] * Right.mat[0][j] +
                                mat[i][1] * Right.mat[1][j] +
                                mat[i][2] * Right.mat[2][j] +
                                mat[i][3] * Right.mat[3][j];
            }
        }

        return Ret;
    }
};



#endif //OPENGLCPP_MATRIX4F_H
