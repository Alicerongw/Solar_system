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


    SECTION("Check no acceleration"){

        nbsim::Particle particle(position,velocity);

        particle.integrateTimeStep(acceleration1, 5.0);

        // position and velocity after timestep
        Eigen::Vector3d pos_2(1.0,5.0,0.0);
        Eigen::Vector3d vel_2(0.0,1.0,0.0);

        REQUIRE(particle.getPostion().isApprox(pos_2));
        REQUIRE(particle.getVelocity().isApprox(vel_2));

    }
    





}





