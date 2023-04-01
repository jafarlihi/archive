import React, { useState, useEffect } from 'react';
import { useParams } from 'react-router-dom';
import styled from 'styled-components';
import { DragDropContext } from 'react-beautiful-dnd';
import { useQuery, gql } from '@apollo/client';
import Step from './Step';
import randomcolor from 'randomcolor';
import { Button, Tooltip } from 'antd';
import { EditOutlined } from '@ant-design/icons';
import JobModal from './JobModal';

const Container = styled.div`
display: flex;
margin-left: auto;
margin-right: auto;
width: 100%;
`;

const Header = styled.div`
position: relative;
width: 100%;
height: 40px;
background-color: lightgrey;
display: flex;
align-items: center;
`

const JobBoard: React.FC = (props: any) => {
  const { id } = useParams();
  const [jobModalOpen, setJobModalOpen] = useState(false);
  const { loading, error, data } = useQuery(gql`query getJob($jobId: ID!) {
    jobById(id: $jobId) {
      id
      title
      department {
        id
      }
      tags {
        id
      }
      description
      requirements
      address
      location
      resume
      coverLetter
      pipeline
      candidateSet {
        id
        fullname
        steps {
          id
          step
          candidate {
            id
          }
          job {
            id
          }
        }
      }
    }
  }`, {variables: {jobId: id}});

  const [state, setState] = useState<any>({});

  useEffect(() => {
    if (data) {
      const newState = {candidates: {}, steps: {}, stepOrder: []};
      const pipeline = JSON.parse(data.jobById.pipeline);
      newState.stepOrder = pipeline;
      let steps = {};
      for (let step of pipeline)
        steps[step] = { id: step, title: step, candidateIds: [] };
      newState.steps = steps;

      let candidates = {};
      for (let candidate of data.jobById.candidateSet)
        candidates[candidate.id] = { id: candidate.id, content: candidate };
      newState.candidates = candidates;

      for (let candidate of data.jobById.candidateSet)
        for (let step of candidate.steps)
          newState.steps[Object.keys(newState.steps)[step.step]].candidateIds.push(candidate.id);

      setState(newState);
    }
  }, [data]);

  const onDragEnd = (result: any) => {
    const { destination, source, draggableId } = result;
    if (!destination)
      return;
    if (destination.droppableId === source.droppableId &&
        destination.index === source.index)
      return;

    const start = state.steps[source.droppableId];
    const finish = state.steps[destination.droppableId];

    if (start === finish) {
      const newCandidateIds = Array.from(start.candidateIds);
      newCandidateIds.splice(source.index, 1);
      newCandidateIds.splice(destination.index, 0, draggableId);
      const newStep = {
        ...start,
        candidateIds: newCandidateIds,
      };
      const newState = {
        ...state,
        steps: {
          ...state.steps,
          [newStep.id]: newStep,
        },
      };
      setState(newState);
      return;
    }

    const startCandidateIds = Array.from(start.candidateIds);
    startCandidateIds.splice(source.index, 1);
    const newStart = {
      ...start,
      candidateIds: startCandidateIds,
    };

    const finishCandidateIds = Array.from(finish.candidateIds);
    finishCandidateIds.splice(destination.index, 0, draggableId);
    const newFinish = {
      ...finish,
      candidateIds: finishCandidateIds,
    };

    const newState = {
      ...state,
      steps: {
        ...state.steps,
        [newStart.id]: newStart,
        [newFinish.id]: newFinish,
      },
    };
    setState(newState);


    const droppedState = JSON.parse(data.jobById.pipeline).indexOf(destination.droppableId);
    const body = {
      step: droppedState,
      job: data.jobById.id,
      candidate: result.draggableId,
    }
    fetch(
      process.env.REACT_APP_API_URL + '/cjs/' + data.jobById.candidateSet[result.draggableId - 1].steps[0].id + '/',
      {
        method: 'PUT',
        body: JSON.stringify(body),
        headers: {'Content-Type': 'application/json'}
      }
    );
  };

  return (
    <>
      <JobModal open={jobModalOpen} setOpen={setJobModalOpen} values={{title: data?.jobById.title}} />
      <Header>
        <div style={{ color: 'black', fontWeight: '900', fontSize: '18px', marginLeft: '10px' }}>
          {data?.jobById.title}
          <Tooltip title="Edit">
          <Button icon={<EditOutlined />} shape="circle" style={{ marginLeft: '20px' }} onClick={() => setJobModalOpen(!jobModalOpen) } />
            </Tooltip>
        </div>
      </Header>
    <Container>
      <DragDropContext onDragEnd={onDragEnd}>
        {state.stepOrder?.map(cid => {
          const step = state.steps[cid];
          const elems = step?.candidateIds.map((tid: any) => state.candidates[tid]);
          return <Step key={cid} step={step} candidates={elems} themeColor={randomcolor()} />
        })}
      </DragDropContext>
    </Container>
    </>
  );
};

export default JobBoard;
