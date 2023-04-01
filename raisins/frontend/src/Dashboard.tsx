import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Filler,
  Legend,
} from 'chart.js';
import { useEffect, useState } from 'react';
import { Line } from 'react-chartjs-2';
import { useQuery, gql } from '@apollo/client';

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Filler,
  Legend
);

export const options = {
  responsive: true,
  maintainAspectRatio: false,
  plugins: {
    legend: {
      position: 'top' as const,
    },
    title: {
      display: true,
      text: 'Candidates chart',
    },
  },
};

function Dashboard() {
  const { loading, error, data: gqlData, refetch } = useQuery(gql`{
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
      createdAt
    }
  }`);

  const [data, setData] = useState<any>(null);
  const labels: string[] = [];
  useEffect(() => {


    labels.push(new Date().toISOString().split('T')[0]);
    for (let i = 15; i != 0; i--) {
      const date = new Date();
      date.setDate(new Date().getDate() - i);
      labels.push(date.toISOString().split('T')[0]);
    }
    labels.sort();
if(gqlData)
      setData({
        labels,
        datasets: [
          {
            fill: true,
            label: 'Candidates',
            data: labels.map((d) => {
              let res = 0;
              for (let c of gqlData.allCandidates)
                if (new Date(Date.parse(c.createdAt)).toISOString().split('T')[0] == d)
                  res++;
              return res;
              }),
              borderColor: 'rgb(53, 162, 235)',
            backgroundColor: 'rgba(53, 162, 235, 0.5)',
          },
        ],
      });


  }, [gqlData]);



  return (
    <div style={{ height: '500px' }}>
      {data ?
      <Line options={options} data={data} />
      : <></>
      }
    </div>
  );
}

export default Dashboard;
