/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   CrossEntropy.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:47 PM
 */

#include "loss/CrossEntropy.h"
#include "ann/functions.h"

CrossEntropy::CrossEntropy(LossReduction reduction): ILossLayer(reduction)
{
    
}

CrossEntropy::CrossEntropy(const CrossEntropy& orig):
ILossLayer(orig)
{
}

CrossEntropy::~CrossEntropy() 
{
}

double CrossEntropy::forward(xt::xarray<double> Y, xt::xarray<double> t)
{
    //YOUR CODE IS 
    m_aCached_Ypred = Y;
    m_aYtarget = t;       
    if (m_eReduction == REDUCE_MEAN) 
    {
        return cross_entropy(Y, t, true);
    } 
    return cross_entropy(Y, t, false);


    
}
xt::xarray<double> CrossEntropy::backward() 
{
    //YOUR CODE IS HERE
    double Nnorm = (m_eReduction == REDUCE_MEAN) ? (double)m_aYtarget.shape()[0] : 1.0;
    auto DY = - (m_aYtarget / (m_aCached_Ypred + 1e-7)) / Nnorm;
    return DY;
}