import '../style.scss';
import {Parallax, ParallaxLayer} from "@react-spring/parallax";
const layer1 = require('../img/parallax/5.png');
const layer2 = require('../img/parallax/4.png');
// const layer3 = require('../img/parallax/layer-03.png');
// const layer4 = require('../img/parallax/layer-04.png');
// const layer5 = require('../img/parallax/layer-05.png');
const layer6 = require('../img/parallax/2.png');
const layer7 = require('../img/parallax/1.png');

function Home() {
  return (
    <div>
          <Parallax pages={1.2}>
            <ParallaxLayer
              offset={0}
              speed={0.5}
              factor={1.4}
              style={{
                backgroundImage: `url(${layer7})`,
                backgroundSize: 'cover',
                backgroundPosition: 'center'
              }}
            ></ParallaxLayer>
            <ParallaxLayer
          offset={0}
          speed={0.8}
          factor={1}
          style={{
            backgroundImage: `url(${layer6})`,
            backgroundSize: 'cover',
            backgroundPosition: 'center'
          }}
            ></ParallaxLayer>
            {/* <ParallaxLayer
          offset={0.9999}
          speed={1.5}
          factor={1.1}
          style={{
            backgroundImage: `url(${layer5})`,
            backgroundSize: 'cover',
            backgroundPosition: 'center'
          }}
            ></ParallaxLayer> */}
            {/* <ParallaxLayer
                    offset={0.9999}
                    speed={3}
                    factor={2.1}
                    style={{
                        backgroundImage: `url(${layer4})`,
                        backgroundSize: 'cover',
                        backgroundPosition: 'center'
                    }}
            ></ParallaxLayer>
            <ParallaxLayer
                    offset={0}
                    speed={2}
                    factor={4}
                    style={{
                        backgroundImage: `url(${layer3})`,
                        backgroundSize: 'contain',
                        backgroundPosition: 'center'
                    }}
            ></ParallaxLayer> */}
            <ParallaxLayer
                    offset={0.87}
                    speed={1}
                    factor={0.4}
                    style={{
                        backgroundImage: `url(${layer2})`,
                        backgroundSize: 'cover',
                        backgroundPosition: 'center'
                    }}
            ></ParallaxLayer>
            <ParallaxLayer
                offset={0.9999}
                speed={1}
                factor={1.1}
                style={{
                    backgroundImage: `url(${layer1})`,
                    backgroundSize: 'cover',
                    backgroundPosition: 'center'
                }}
            ></ParallaxLayer>
          </Parallax>
         </div>
      )
    }

export default Home

