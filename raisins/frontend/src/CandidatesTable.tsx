import { Tabs, Card, Table } from 'antd';
import { useLocation } from 'react-router-dom';
import { useQuery, gql } from '@apollo/client';
import { useNavigate } from 'react-router-dom';
import styled from 'styled-components';
import TimeAgo from 'javascript-time-ago';
import { useEffect } from 'react';
import en from 'javascript-time-ago/locale/en'
import Avatar from './Avatar';

const Container = styled.div`
display: flex;
flex-direction: column;
align-items: center;
background-color: #F3F3F3;
width: 100%;
height: 100vh;
`;

TimeAgo.addDefaultLocale(en)

function CandidatesTable() {
  const navigate = useNavigate();
  const location = useLocation();
  const { loading, error, data, refetch } = useQuery(gql`{
    allCandidates {
        id
        fullname
      email
      phone
      jobs {
        id
        title
        pipeline
      }
      address
      salaryExpectation
      timezone
      steps {
        id
        job {
          id
          title
        }
        step
      }
    }
  }`);

  useEffect(() => {
    refetch();
  }, [refetch]);

  const columns = [
    {
      title: 'Full name',
      key: 'title',
      render: e => {
        return <div style={{ display: 'flex', alignItems: 'center' }}><Avatar userId={e.id} size={2} text={`${e.fullname.split(' ')[0][0]}${e.fullname.split(' ')[1][0]}`}/>{e.fullname}</div>
      }
    },
      {
      title: 'Jobs',
      key: 'jobs',
      render: e => {
        return <>{e?.jobs?.[0]?.title}</> 
      }
    },
    {
      title: 'Stage',
      key: 'stage',
      render: e => {
        return <>{e?.jobs?.[0]?.pipeline && JSON.parse(e.jobs[0].pipeline)[e.steps[0].step]}</>
      }
    },
  ];

  if (loading)
    return <span>Loading...</span>

  return (
    <>
<Table dataSource={data?.allCandidates} columns={columns} onRow={(record, index) => {
        return {
          onClick: (e) => navigate('/candidate/' + record.id),
        };
      }}></Table>

    </>
  )
}

export default CandidatesTable;
