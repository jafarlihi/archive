import { Tabs, Card, Table } from 'antd';
import { ThunderboltOutlined, FieldTimeOutlined } from '@ant-design/icons';
import { useQuery, gql } from '@apollo/client';
import { useNavigate } from 'react-router-dom';
import styled from 'styled-components';
import TimeAgo from 'javascript-time-ago';
import { useEffect } from 'react';
import en from 'javascript-time-ago/locale/en'

const Container = styled.div`
display: flex;
flex-direction: column;
align-items: center;
background-color: #F3F3F3;
width: 100%;
height: 100vh;
`;


TimeAgo.addDefaultLocale(en)

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

function JobsTable() {
  const navigate = useNavigate();
  const { loading, error, data } = useQuery(gql`{ allJobs { id, title, department {
    id, name
  }, tags {
    id
  }, description, requirements, address, location, resume, coverLetter, phone, pipeline, updatedAt, createdAt, candidateSet {
    id,
  }
  } }`);

  const columns = [
    {
      title: 'Title',
      dataIndex: 'title',
      key: 'title',
    },
    {
      title: 'Department',
      dataIndex: ['department', 'name'],
      key: 'department',
    },
    {
      title: 'Candidates',
      dataIndex: ['candidateSet', 'length'],
      key: 'candidateCount',
    },
    {
      title: 'Updated',
      key: 'updatedAt',
      render: e => {
        return new TimeAgo('en-US').format(new Date(e.updatedAt));
      }
    },
  ];

  if (loading)
    return <span>Loading...</span>

  return (
    <>
      <Table dataSource={data?.allJobs} columns={columns} onRow={(record, index) => {
        return {
          onClick: (e) => navigate('/job/' + record.id),
        };
      }}></Table>
    </>
  )
}

export default JobsTable;
