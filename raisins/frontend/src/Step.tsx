import React, { useEffect, useState } from 'react';
import styled from 'styled-components';
import { Droppable } from 'react-beautiful-dnd';
import CandidateDraggable from './CandidateDraggable';

const Container = styled.div`
margin: 8px;
border-radius: 2px;
min-width: 220px;
display: flex;
flex-direction: column;
`;

const Title = styled.h3`
padding: 8px;
font-weight: bold;
text-decoration: underline;
text-decoration-thickness: 5px;
`;

const CandidateList = styled.div<{ isDraggingOver: boolean, themeColor: string }>`
padding: 8px;
transition: background-color 0.2s ease;
background-color: ${props => (props.isDraggingOver ? props.themeColor : 'white')};
flex-grow: 1;
min-height: 100px;
`;

class InnerList extends React.Component<{ candidates: any, color: any }> {
  shouldComponentUpdate(nextProps: any) {
    if (nextProps === this.props.candidates) return false;
    return true;
  }
  render() {
    return this.props.candidates.map((t: any, i: number) => (
      <CandidateDraggable key={t.id} candidate={t} index={i} color={ this.props.color }/>
    ));
  }
}

function Step(props: any) {
  const [enabled, setEnabled] = useState(false);

  useEffect(() => {
    const animation = requestAnimationFrame(() => setEnabled(true));

    return () => {
      cancelAnimationFrame(animation);
      setEnabled(false);
    };
  }, []);

  if (!enabled) {
    return null;
  }

  return (
    <Container>
      <Title style={{ textDecorationColor: props.themeColor }}>{props.step.title}</Title>
      <Droppable droppableId={props.step.id}>
        {(provided, snapshot) => (
          <CandidateList
            {...provided.droppableProps}
            ref={provided.innerRef}
            isDraggingOver={snapshot.isDraggingOver}
            themeColor={props.themeColor}
          >
            <InnerList candidates={props.candidates} color={props.themeColor} />
            {provided.placeholder}
          </CandidateList>
        )}
      </Droppable>
    </Container>
  );
}

export default Step;
