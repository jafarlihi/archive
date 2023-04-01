import { useEffect, useState } from 'react';
import styled from 'styled-components';
import ColorHash from 'color-hash';
import ContrastColor from 'contrast-color';

const Circle = styled.div<{ size: number }>`
background-color: ${props => props.color};
border-radius: 50%;
height: ${props => props.size}rem;
text-align: center;
width: ${props => props.size}rem;
display: inline-grid;
margin-left: 5px;
margin-right: 5px;
`;

const Initials = styled.span<{ size: number }>`
font-size: calc(${props => props.size}rem / 2);
line-height: 1;
position: relative;
top: calc(${props => props.size}rem / 4);
color: ${props => props.color};
`;

function Avatar(props: any) {
  const [avatarExists, setAvatarExists] = useState(false);
  const colorHash = new ColorHash();
  const contrastColor = new ContrastColor();

  useEffect(() => {
    try {
      require(`./avatars/${props.userId}`);
      setAvatarExists(true);
    } catch (err) {
      setAvatarExists(false);
    }
  }, []);

  return (
    avatarExists ?
      <img src={`./avatars/${props.userId}`} /> :
      <Circle size={props.size} color={colorHash.hex(props.text)}><Initials size={props.size} color={contrastColor.contrastColor({ bgColor: colorHash.hex(props.text)})}>{props.text}</Initials></Circle>
  );
}

export default Avatar;
