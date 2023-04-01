import { useEffect, useState } from 'react';
import NewCandidateModal from './NewCandidateModal';
import JobModal from './JobModal';
import BottomBar from './BottomBar';
import { useQuery, gql } from '@apollo/client';

function Layout(props: any) {
  const [newCandidateModalOpen, setNewCandidateModalOpen] = useState(false);
  const [newJobModalOpen, setJobModalOpen] = useState(false);
  const [users, setUsers] = useState([]);

  const { loading, error, data, refetch } = useQuery(gql`{ allJobs { id, title, department {
    id,
    name
  }, tags {
    id
  }, description, requirements, address, location, resume, coverLetter, phone, pipeline, candidateSet {
    id,
  }
  } }`);

  useEffect(() => {
    const getUsers = async () => {
      const response = await (await fetch(process.env.REACT_APP_API_URL + '/auth/users/', {
        method: 'GET',
        headers: { 'Authorization': 'JWT ' + localStorage.getItem('access')}
      })).json();
      setUsers(response.results);
      console.log(response);
    }
    getUsers();
  }, []);

  return (
    <>
      <NewCandidateModal open={newCandidateModalOpen} setOpen={setNewCandidateModalOpen} jobs={data?.allJobs} refetch={refetch} />
      <JobModal open={newJobModalOpen} setOpen={setJobModalOpen} departments={[...new Set(data?.allJobs.map((j) => j.department))]} jobs={data?.allJobs} users={users} refetch={refetch} />
      {props.children}
      <BottomBar setNewCandidateModalOpen={setNewCandidateModalOpen} setJobModalOpen={setJobModalOpen} />
    </>
  );
}

export default Layout;
