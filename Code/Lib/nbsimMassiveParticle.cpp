#include "nbsimMassiveParticle.h"
#include <math.h>
#include <iostream>
#include <omp.h>


namespace nbsim{

    MassiveParticle::MassiveParticle(Eigen::Vector3d Position, Eigen::Vector3d Velocity,double Mu):Particle(Position, Velocity){
        
        Mu_ = Mu;
        Acceleration_ << 0.0,0.0,0.0;
        
    }

    MassiveParticle::~MassiveParticle(){}


    double MassiveParticle::getMu() const{

        return Mu_;

    }

    void MassiveParticle::addAttractor(std::shared_ptr<MassiveParticle> attractor){

        ListofParticles.push_back(attractor);

    }


    void MassiveParticle::removeAttractor(std::shared_ptr<MassiveParticle> attractor){

        auto  it = std::find(ListofParticles.begin(), ListofParticles.end(), attractor);

        if (it != ListofParticles.end()){

            it = ListofParticles.erase(it);
        }

    }


    void MassiveParticle::calculateAcceleration(){

        Eigen::Vector3d Acceleration_copy(0.0,0.0,0.0);

        for(int i = 0; i < ListofParticles.size(); i++){

            Eigen::Vector3d r_i = getPosition() - ListofParticles[i]->getPosition();

            Eigen::Vector3d r_i_normalized = r_i / sqrt(r_i.dot(r_i));

            Acceleration_copy = Acceleration_copy - (ListofParticles[i]->getMu() / (r_i.dot(r_i))) * r_i_normalized;
        }

        Acceleration_ = Acceleration_copy;
        
    }


    void MassiveParticle::integrateTimestep(const double& timestep){

        setPosition(getPosition() +  timestep * getVelocity());

        setVelocity(getVelocity() +  timestep * Acceleration_);
        
    }

        
}    