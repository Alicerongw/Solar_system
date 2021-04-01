#include "nbsimParticle.h"
#include <iostream>

namespace nbsim{

    Particle::Particle(Eigen::Vector3d Position, Eigen::Vector3d Velocity){

        Position_ = Position;

        Velocity_ = Velocity;

    }

    Particle::~Particle(){}

    Eigen::Vector3d Particle::getPosition() const{

        return Position_;

    }
    
    Eigen::Vector3d Particle::getVelocity() const{

        return Velocity_;

    }

                        
    void Particle::integrateTimeStep(Eigen::Vector3d acceleration, double timestep){

        Eigen::Vector3d Velocity_ini = Velocity_;

        Velocity_ = Velocity_ + acceleration * timestep;

        Position_ = Position_ + (Velocity_ini + Velocity_) * 0.5 * timestep;


    }



}
