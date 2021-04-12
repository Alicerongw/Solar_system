#include "nbsimParticle.h"

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

    void Particle::setPosition(Eigen::Vector3d position){

       Position_ = position;

    }
    
    void Particle::setVelocity(Eigen::Vector3d velocity) {

        Velocity_ = velocity;

    }

                        
    void Particle::integrateTimeStep(Eigen::Vector3d acceleration, double timestep){

        Position_ = Position_ + Velocity_ * timestep;

        Velocity_ = Velocity_ + acceleration * timestep;

    }


}
