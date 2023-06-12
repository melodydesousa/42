import React from "react";
import '../style.scss';
import {IParallax, Parallax, ParallaxLayer} from "@react-spring/parallax";
import { string } from "prop-types";
const layer1 = require('../img/parallax/1.png');
const layer2 = require('../img/parallax/2.png');
const layer3 = require('../img/parallax/3.png');
const layer4 = require('../img/parallax/4.png');
const layer5 = require('../img/parallax/5.png');

function Home() {
  return (
        <div>
            <Parallax pages={1.1}>
              {/* <ParallaxLayer
            offset={-1}
            speed={1}
            factor={2}
            style={{
              backgroundImage: `url(${layer4})`,
              backgroundSize: 'cover',
              backgroundPosition: 'center'
                      }}
              ></ParallaxLayer> */}
            {/* <ParallaxLayer
                offset={0}
                speed={1}
                factor={1}
                style={{
                    backgroundImage: `url(${layer1})`,
                    backgroundSize: 'cover',
                    backgroundPosition: 'center'
                }}
            ></ParallaxLayer> */}
            {/* <ParallaxLayer
          offset={-1}
          speed={1}
          factor={1}
          style={{
            backgroundImage: `url(${layer5})`,
            backgroundSize: 'cover',
            backgroundPosition: 'center'
          }}
            ></ParallaxLayer> */}
            <ParallaxLayer
                    offset={0}
                    speed={2}
                    factor={1}
                    style={{
                        backgroundImage: `url(${layer3})`,
                        backgroundSize: 'cover',
                        backgroundPosition: 'center',
                    }}
            ></ParallaxLayer>
            {/* <ParallaxLayer
                    offset={0}
                    speed={1}
                    factor={1}
                    style={{
                        backgroundImage: `url(${layer2})`,
                        backgroundSize: 'cover',
                        backgroundPosition: 'center'
                    }}
            ></ParallaxLayer> */}
            
          </Parallax>
         </div>
      )
    }

export default Home

