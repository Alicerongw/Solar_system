#include "nbsimMassiveParticle.h"
#include <math.h>


const double gravitational_constant = 6.754*pow(10,-11);

namespace nbsim{

    MassiveParticle::MassiveParticle(Eigen::Vector3d Position, Eigen::Vector3d Velocity,double Mass):Particle(Position, Velocity){
        
        Mass_ = Mass;
        Acceleration_ << 0.0,0.0,0.0;
        
    }

    MassiveParticle::~MassiveParticle(){}


    double MassiveParticle::getMu(){

        return gravitational_constant * Mass_;

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

        
        for(int i = 0; i < ListofParticles.size(); i++){

            Eigen::Vector3d r_i = getPosition() - ListofParticles[i]->getPosition();

            Eigen::Vector3d r_i_normalized = r_i / sqrt(r_i.dot(r_i));

            Acceleration_ = Acceleration_ - r_i_normalized * (ListofParticles[i]->getMu() / (r_i.dot(r_i)));
        }

    }


    void MassiveParticle::integrateTimestep(const double& timestep){

        Velocity_ = Velocity_ + Acceleration_ * timestep;

        Position_ = Position_ + Velocity_ * timestep;

    }

        
}    