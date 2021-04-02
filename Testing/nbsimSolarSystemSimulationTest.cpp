#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimParticle.h"
#include "nbsimMassiveParticle.h"
#include <iostream>
#include <vector>

const double gravitational_constant = 6.754*pow(10,-11);

TEST_CASE( "Test for acceleration of particle", "[some group identifier]" ) {

    Eigen::Vector3d position(1.0,0.0,0.0);
    Eigen::Vector3d velocity(0.0,1.0,0.0);
    Eigen::Vector3d acceleration1(0.0,0.0,0.0);
    Eigen::Vector3d acceleration2(2.0,2.0,2.0);


    SECTION("Check particle movement when there is no acceleration"){

        // create an instance of Particle class
        nbsim::Particle particle(position,velocity);

        particle.integrateTimeStep(acceleration1, 5.0);

        // position and velocity after timestep
        Eigen::Vector3d pos_2(1.0,5.0,0.0);
        Eigen::Vector3d vel_2(0.0,1.0,0.0);

        REQUIRE(particle.getPosition().isApprox(pos_2));
        REQUIRE(particle.getVelocity().isApprox(vel_2));

    }
    
    SECTION("Check particle movement when there is constant acceleration"){

        // create an instance of Particle class
        nbsim::Particle particle(position,velocity);

        particle.integrateTimeStep(acceleration2, 5.0);

        // position and velocity after timestep
        Eigen::Vector3d pos_2(26.0,30.0,25.0);
        Eigen::Vector3d vel_2(10.0,11.0,10.0);

        REQUIRE(particle.getPosition().isApprox(pos_2));
        REQUIRE(particle.getVelocity().isApprox(vel_2));

    }


    SECTION("Check particle movement when there is fictitious centripetal acceleration"){

        // create an instance of Particle class
        nbsim::Particle particle(position,velocity);

        // after stepping through 2𝜋 worth of time (number of steps * step length)
        for(int i = 1; i <=1000; i++){

            particle.integrateTimeStep(-particle.getPosition(), 2*M_PI/1000);

        }

        REQUIRE(particle.getPosition().isApprox(position,0.01));
        REQUIRE(particle.getVelocity().isApprox(velocity,0.01));

    }

}



TEST_CASE( "Test for acceleration of MassiveParticle", "[some group identifier]" ) {

    Eigen::Vector3d position1(1.0,0.0,0.0);
    Eigen::Vector3d position2(-1.0,0.0,0.0);
    Eigen::Vector3d velocity1(0.0,0.5,0.0);
    Eigen::Vector3d velocity2(0.0,-0.5,0.0);
    
    SECTION("check single MassiveParticle with no attractors will travel with a constant velocity"){

        // create an intance of MassiveParticle class
        std::shared_ptr<nbsim::MassiveParticle> M_Particle1(new nbsim::MassiveParticle(position1,velocity1,1/gravitational_constant));

        M_Particle1->calculateAcceleration();
        M_Particle1->integrateTimestep(5.0);

        REQUIRE(M_Particle1->getVelocity().isApprox(velocity1));

    }

}


