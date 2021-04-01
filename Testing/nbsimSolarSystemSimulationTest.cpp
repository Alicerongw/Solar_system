#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimParticle.h"
#include <iostream>
#include <vector>



TEST_CASE( "Test for acceleration", "[some group identifier]" ) {

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

        REQUIRE(particle.getPostion().isApprox(pos_2));
        REQUIRE(particle.getVelocity().isApprox(vel_2));

    }
    
    SECTION("Check particle movement when there is constant acceleration"){

        // create an instance of Particle class
        nbsim::Particle particle(position,velocity);

        particle.integrateTimeStep(acceleration2, 5.0);

        // position and velocity after timestep
        Eigen::Vector3d pos_2(26.0,30.0,25.0);
        Eigen::Vector3d vel_2(10.0,11.0,10.0);

        REQUIRE(particle.getPostion().isApprox(pos_2));
        REQUIRE(particle.getVelocity().isApprox(vel_2));

    }


    SECTION("Check particle movement when there is fictitious centripetal acceleration"){

        // create an instance of Particle class
        nbsim::Particle particle(position,velocity);

        // after stepping through 2𝜋 worth of time (number of steps * step length)
        for(int i = 1; i <=1000; i++){

            particle.integrateTimeStep(-particle.getPostion(), 2*M_PI/1000);

        }

        REQUIRE(particle.getPostion().isApprox(position,0.01));
        REQUIRE(particle.getVelocity().isApprox(velocity,0.01));

    }

}





