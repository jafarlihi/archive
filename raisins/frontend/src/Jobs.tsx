import { Tabs, Card } from 'antd';
import { ThunderboltOutlined, FieldTimeOutlined } from '@ant-design/icons';
import { useQuery, gql } from '@apollo/client';
import { useNavigate } from 'react-router-dom';
import styled from 'styled-components';

const Container = styled.div`
display: flex;
flex-direction: column;
align-items: center;
background-color: #F3F3F3;
width: 100%;
height: 100vh;
`;

function JobPreview(props: any) {
  const navigate = useNavigate();

  const onJobClick = () => {
    navigate('/job/' + props.job.id);
  };

  return (
    <Card size="small" title={props.job.title} extra={<a href="#">More</a>} style={{ width: 1000, height: 150, marginTop: '5px', position: 'relative' }} onClick={onJobClick}>
      {props.job.remote ? 'Remote' : props.job.country ? (props.job.country + ' ' + props.job.city) : <></>}
      <div style={{ position: 'absolute', bottom: '0' }}>
        {props.job.candidateSet.length} {props.job.candidateSet.length === 1 ? 'candidate' : 'candidates'}
      </div>
    </Card>
  );
}

function Jobs() {
  const { loading, error, data } = useQuery(gql`{ allJobs { id, title, department {
    id
  }, tags {
    id
  }, description, requirements, address, location, resume, coverLetter, phone, pipeline, candidateSet {
    id,
  }
  } }`);

  const tabs = [
    {
      label: (<span><ThunderboltOutlined />Active</span>),
      key: 'active',
      children: <Container>{data?.allJobs?.map((j) => (
        <JobPreview key={j.id} job={j} />
      ))}</Container>
    },
    { label: (<span><FieldTimeOutlined />Archived</span>), key: 'archived', children: 'Content 2' }
  ];

  if (loading)
    return <span>Loading...</span>

  return (
    <>
      <Tabs items={tabs}></Tabs>
    </>
  )
}

export default Jobs;
