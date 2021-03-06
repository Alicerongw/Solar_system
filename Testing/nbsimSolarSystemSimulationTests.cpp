#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimParticle.h"
#include "nbsimMassiveParticle.h"
#include <iostream>
#include <vector>


TEST_CASE( "Test for acceleration of particle", "[Particle]" ) {

    Eigen::Vector3d position(1.0,0.0,0.0);
    Eigen::Vector3d velocity(0.0,1.0,0.0);
    Eigen::Vector3d acceleration1(0.0,0.0,0.0);
    Eigen::Vector3d acceleration2(1.0,1.0,1.0);


    SECTION("Check particle movement when there is no acceleration"){

        // create an instance of Particle class
        nbsim::Particle particle(position,velocity);

        particle.integrateTimeStep(acceleration1, 0.01);

        // position and velocity after timestep
        Eigen::Vector3d pos_2(1.0,0.01,0.0);
        Eigen::Vector3d vel_2(0.0,1.0,0.0);

        REQUIRE(particle.getPosition().isApprox(pos_2));
        REQUIRE(particle.getVelocity().isApprox(vel_2));

    }
    
    SECTION("Check particle movement when there is constant acceleration"){

        // create an instance of Particle class
        nbsim::Particle particle(position,velocity);

        particle.integrateTimeStep(acceleration2, 0.01);

        // position and velocity after timestep
        Eigen::Vector3d pos_2(1.0,0.01,0.0);
        Eigen::Vector3d vel_2(0.01,1.01,0.01);

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

       
        REQUIRE(particle.getPosition().isApprox(position,0.02));
        REQUIRE(particle.getVelocity().isApprox(velocity,0.02));

    }

}



TEST_CASE( "Test for acceleration of MassiveParticle", "[MassiveParticle]" ) {

    Eigen::Vector3d position1(1.0,0.0,0.0);
    Eigen::Vector3d position2(-1.0,0.0,0.0);
    Eigen::Vector3d velocity1(0.0,0.5,0.0);
    Eigen::Vector3d velocity2(0.0,-0.5,0.0);
    
    SECTION("check single MassiveParticle with no attractors will travel with a constant velocity"){

        // create an intance of MassiveParticle class
        std::shared_ptr<nbsim::MassiveParticle> M_Particle1(new nbsim::MassiveParticle(position1,velocity1,1));

        M_Particle1->calculateAcceleration();
        M_Particle1->integrateTimestep(5.0);

        REQUIRE(M_Particle1->getVelocity().isApprox(velocity1));

    }

    SECTION("check two MassiveParticles which gravitationally attracts each other"){

        // create two intances of MassiveParticle class
        std::shared_ptr<nbsim::MassiveParticle> M_Particle1(new nbsim::MassiveParticle(position1,velocity1,1.0));
        std::shared_ptr<nbsim::MassiveParticle> M_Particle2(new nbsim::MassiveParticle(position2,velocity2,1.0));


        M_Particle1->addAttractor(M_Particle2);
        M_Particle2->addAttractor(M_Particle1);

        for(int i = 0; i < 1000; i++){

            M_Particle1->calculateAcceleration();
            M_Particle2->calculateAcceleration();

            M_Particle1->integrateTimestep(4*M_PI/1000);
            M_Particle2->integrateTimestep(4*M_PI/1000);
            
        }

        double distance = sqrt((M_Particle1->getPosition() - M_Particle2->getPosition()).dot(M_Particle1->getPosition() - M_Particle2->getPosition()));

        REQUIRE(distance == Approx(2.0).epsilon(0.1));

    }

}


