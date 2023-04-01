import styled from 'styled-components';
import { Draggable } from 'react-beautiful-dnd';
import Avatar from './Avatar';

const Container = styled.div<{ isDragging: boolean, color: any }>`
border: 1px solid ${props => props.color};
border-radius: 2px;
padding: 8px;
margin-bottom: 8px;
background-color: ${props => (props.isDragging ? props.color : 'white')};
border-radius: 5px;
display: flex;
align-items: center;
`;

function CandidateDraggable(props) {
  console.log(props);
  return (
    <Draggable draggableId={props.candidate.id} index={props.index}>
      {(provided, snapshot) => (
        <Container
          {...provided.draggableProps}
          {...provided.dragHandleProps}
          ref={provided.innerRef}
          isDragging={snapshot.isDragging}
          color={props.color}
        >
          <Avatar userId={props.candidate.id} size={2} text={`${props.candidate.content.fullname.split(' ')[0][0]}${props.candidate.content.fullname.split(' ')[1][0]}`}></Avatar>
          {props.candidate.content.fullname}
        </Container>
      )}
    </Draggable>
  );
}

export default CandidateDraggable;
